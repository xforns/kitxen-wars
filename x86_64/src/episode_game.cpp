#include "episode_game.h"
#include "defs.h"
#include <iostream>

#define TIME_STEP 500

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
	
	_halt_action = false;
	
	_last_clock = clock();
	
	_background.start();
	
	_character = make_shared<character>();
	_character.get()->start();
	
	_collision_system.set_bounds(0,0,320,200);
	_collision_system.start();
	
	_collision_system.add(_character);
}


void episode_game::stop()
{
	// bg
	_background.stop();
	
	// character
	_character.get()->stop();
	
	_collision_system.remove(_character);
	
	// enemies
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
	
	// collision system
	_collision_system.stop();
	
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
	double diff = ( clock() - _last_clock );
	if(diff>=TIME_STEP)
	{
		_halt_action = true;
		// main character logic
		
		
		// enemies logic
		
		if(rand()%TIME_STEP>498)
		{
			add_enemies(1);
		}
		
		auto ite = _enemies.begin();
		while(ite!=_enemies.end())
		{
			enemy_ptr ptr = *(ite++);
			enemy *obj = ptr.get();
			obj->update();
		}
		
		// character bullets logic
		while(_add_bullets>0)
		{
			bullet_ptr obj_ptr = make_shared<bullet>();
			obj_ptr.get()->x_y(_character.get()->cx(),_character.get()->yh());
			obj_ptr.get()->start();
			
			_bullets.push_back(obj_ptr);
			_collision_system.add(obj_ptr);
			
			_add_bullets--;
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
		
		// enemies bullets logic
		for(auto it = _dead_enemies.begin(); it!=_dead_enemies.end();++it)
		{
			entity_ptr ptr = *it;
			ptr.get()->stop();
			_collision_system.remove(ptr);
			
			shared_ptr<enemy> eptr = dynamic_pointer_cast<enemy>(ptr);
			
			_enemies.erase(remove_if(_enemies.begin(),_enemies.end(),ptr_contains(eptr.get())));
		}
		_dead_enemies.clear();
		
		// energy logic
		
		// bomb logic
		
		_last_clock = clock();
		
		_halt_action = false;
	}
	
	_character.get()->update();
}


void episode_game::draw()
{
    glColor3f(1.f,1.f,1.f);
	
    _background.draw();
	
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
	
    draw_enemies();
	
	draw_main_character();
	
	draw_bullets();
	
	glDisable(GL_BLEND);
}


void episode_game::draw_main_character()
{
	_character.get()->draw();
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
	}
	else if(param.msg_type==MSG_COLLISION)
	{
		//cout << "Collision! " << param.a << " - " << param.b << endl << flush;
		// bullet to enemy collision
		if( ( (param.a==TYPE_ENEMY) && (param.b==TYPE_BULLET) )
			|| ( (param.a==TYPE_BULLET) && (param.b==TYPE_ENEMY) ) )
		{
			if(!_halt_action)
			{
				_dead_enemies.push_back( param.a==TYPE_ENEMY ? param.o1 : param.o2 );
			}
		}
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

