#include "episode_game.h"
#include "defs.h"
#include <iostream>

#define TIME_STEP 500
#define MAX_ENEMIES 20

/****************************************************************

							public

****************************************************************/


episode_game::episode_game()
{
}


episode_game::~episode_game()
{
}


void episode_game::start()
{
	episode::start();
	
	messaging::getInstance().add(this);
	
	_add_bullets = 0;
	
	_character_explosion = NULL;
	
	_bomb = NULL;
	
	_add_bomb = false;
	
	_kill_all_enemies = false;
	
	_kill_all_enemies_enable = false;
	
	_background.start();
	
	_character = make_shared<character>();
	_character.get()->start();
	
	_collision_system.set_bounds(0,0,320,200);
	_collision_system.start();
	
	_collision_system.add(_character);
	
	_energy = new energy();
	_energy->start();
}


void episode_game::stop()
{
	// bg
	_background.stop();
	
	// character
	if(_character.get()!=NULL)
	{
		_character.get()->stop();
	
		_collision_system.remove(_character);
	}
	if(_character_explosion!=NULL)
	{
		delete _character_explosion;
	}
	if(_bomb!=NULL)
	{
		_bomb->stop();
		delete _bomb;
	}
	
	// enemies
	asset_helper::getInstance().unload_texture(asset_helper::ENEMY);
	
	std::for_each( _enemies.begin(), _enemies.end(), [](shared_ptr<enemy> obj)
		{
			obj.get()->stop();
		});
	_enemies.clear();
	
	// bullets
	std::for_each( _bullets.begin(), _bullets.end(), [](shared_ptr<bullet> obj)
		{
			obj.get()->stop();
		});
	_bullets.clear();
	
	// explosions
	asset_helper::getInstance().unload_texture(asset_helper::EXPLOSION);
	
	// collision system
	_collision_system.stop();
	
	// energy
	_energy->stop();
	delete _energy;
	
	// messaging
	messaging::getInstance().remove(this);
	
	episode::stop();
}


void episode_game::pause()
{
	episode::pause();
}


void episode_game::update()
{
	// main character
	if( (_character.get()!=NULL) && (_character.get()->is_dead()) )
	{
		_character.get()->stop();
		
		// add an explosion
		_character_explosion = new explosion();
		_character_explosion->x_y(_character.get()->x(),_character.get()->y());
		_character_explosion->start();
		
		_collision_system.remove(_character);
		
		_character.reset();
	}
	if(_character_explosion!=NULL)
	{
		_character_explosion->update();
		if(_character_explosion->is_dead())
		{
			_character_explosion->stop();
			delete _character_explosion;
			_character_explosion = NULL;
			
			// end of game
			_current_episode_status = ENDED;
		}
	}
		
	// enemies
	
	if( (rand()%TIME_STEP>480))
	{
		add_enemies(1);
	}
	
	auto ite = _enemies.begin();
	while(ite!=_enemies.end())
	{
		enemy_ptr ptr = *(ite++);
		enemy *obj = ptr.get();
		
		if(_kill_all_enemies)
		{
			obj->set_dead(true);
		}
		// enemy is dead: remove it
		if(obj->is_dead())
		{
			double x = ptr.get()->x();
			double y = ptr.get()->y();
			
			obj->stop();
			
			_collision_system.remove(ptr);
			
			_enemies.erase(remove_if(_enemies.begin(),_enemies.end(),ptr_contains(ptr.get())));
			
			// add an explosion
			_explosions.push_back(NULL);
			_explosions.back() = new explosion();
			_explosions.back()->x_y(x,y);
			_explosions.back()->start();
			
			ite--;
			continue;
		}
		
		obj->update();
	}
	
	if(_kill_all_enemies)
	{
		_kill_all_enemies = false;
		_kill_all_enemies_enable = false;
		_add_bomb = false;
		delete _bomb;
		_bomb = NULL;
	}
	
	// character bullets
	
	if(_character.get()!=NULL)
	{
		while(_add_bullets>0)
		{
			bullet_ptr obj_ptr = make_shared<bullet>();
			obj_ptr.get()->x_y(_character.get()->cx(),_character.get()->yh());
			obj_ptr.get()->start();
		
			_bullets.push_back(obj_ptr);
			_collision_system.add(obj_ptr);
		
			_add_bullets--;
		}
	}
	
	auto itb = _bullets.begin();
	while(itb!=_bullets.end())
	{
		bullet_ptr ptr = *(itb);
		bullet *obj = ptr.get();
		
		// is bullet dead
		if(obj->is_dead())
		{ 
			obj->stop();
			_collision_system.remove(ptr);
			_bullets.erase(remove_if(_bullets.begin(),_bullets.end(),ptr_contains(ptr.get())));
			
			continue;
		}
		itb++;
		
		obj->update();
	}
	
	// energy
	_energy->update();
	
	// bomb
	if( (_add_bomb) && (_kill_all_enemies_enable) )
	{
		_add_bomb = false;
		
		_bomb = new bomb();
		_bomb->x_y(_character.get()->x(),_character.get()->y());
		_bomb->start();
	}
	if(_bomb!=NULL)
	{
		_bomb->update();
	}
	
	// explosions
	
	auto it = _explosions.begin();
	while(it!=_explosions.end())
	{
		(*it)->update();
		
		if((*it)->is_dead())
		{
			(*it)->stop();
			delete *it;
			_explosions.erase(it);
			--it;
		}
		++it;
	}
	
	if(_character.get()!=NULL)
	{
		_character.get()->update();
	}
}


void episode_game::draw()
{
    glColor3f(1.f,1.f,1.f);
	
    _background.draw();
	
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
	
    draw_enemies();
	
	draw_main_character();
	
	draw_bullets();
	
	// draw explosions
	for(auto it = _explosions.begin(); it!=_explosions.end();++it)
	{
		(*it)->draw();
	}
	if(_character_explosion!=NULL)
	{
		_character_explosion->draw();
	}
	
	// bomb
	if(_bomb!=NULL)
	{
		_bomb->draw();
	}
	
	//glDisable(GL_BLEND);
	
	// energy
	_energy->draw();
}


void episode_game::draw_main_character()
{
	if(_character.get()!=NULL)
	{
		_character.get()->draw();
	}
}


void episode_game::draw_enemies()
{
	auto it = _enemies.begin();
	while(it!=_enemies.end())
	{
		enemy_ptr ptr = *(it++);
		enemy *obj = ptr.get();
		obj->draw();
	}
}


void episode_game::draw_bullets()
{
	auto it = _bullets.begin();
	while(it!=_bullets.end())
	{
		bullet_ptr ptr = *(it++);
		bullet *obj = ptr.get();
		obj->draw();
	}
}


/****************************************************************

						observer interface

****************************************************************/


void episode_game::update(const observable_data &param)
{
	if(param.msg_type==MSG_MOUSE)
	{
		// go back to main menu
		if(param.a==LMB_PRESSED)
		{
			observable_data data;
			data.msg_type = MSG_EPISODE;
			data.a = EPISODE_MENU;
			messaging::getInstance().notify(data);
		}
	}
	else if(param.msg_type==MSG_KEYBOARD_S || param.msg_type==MSG_KEYBOARD)
	{
		// new bullet
		if(param.a==32)
		{
			_add_bullets++;
		}
		// bomb
		else if(param.a=='b')
		{
			if( (_bomb==NULL) && (_character.get()!=NULL) )
			{
				_add_bomb = true;
			}
		}
	}
	else if(param.msg_type==MSG_COLLISION)
	{
		// bullet to enemy collision
		if( ( (param.a==TYPE_ENEMY) && (param.b==TYPE_BULLET) )
			|| ( (param.a==TYPE_BULLET) && (param.b==TYPE_ENEMY) ) )
		{
			shared_ptr<enemy> eptr = dynamic_pointer_cast<enemy>(param.a==TYPE_ENEMY ? param.o1 : param.o2);
			if(eptr.get()!=NULL)
			{
				eptr.get()->set_dead(true);
			}
			shared_ptr<bullet> bptr = dynamic_pointer_cast<bullet>(param.a==TYPE_BULLET ? param.o1 : param.o2);
			if(bptr.get()!=NULL)
			{
				bptr.get()->set_dead(true);
			}
		}
	}
	else if(param.msg_type==MSG_BOMB)
	{
		_kill_all_enemies = true;
	}
	else if(param.msg_type==MSG_BOMB_ENABLE)
	{
		_kill_all_enemies_enable = true;
	}
	
}


/****************************************************************

							private

****************************************************************/


void episode_game::add_enemies(int batch)
{
	unsigned int xmin = 50, xmax = 250;
	unsigned int ymin = 120, ymax = 140;
	
	for(int i=0;i<batch;i++)
	{
		unsigned int x = rand() % xmax + xmin;
		unsigned int y = rand() % ymax + ymin;
		
		enemy_ptr ptr = make_shared<enemy>();
		ptr.get()->x_y(x,y);
		ptr.get()->start();
		_enemies.push_back(ptr);
		_collision_system.add(ptr);
	}
}

