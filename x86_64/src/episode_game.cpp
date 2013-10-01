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
	
	_last_clock = clock();
	
	_background.start();
	
	_character->get()->start();
	
	_collision_system.set_bounds(0,0,320,200);
	_collision_system.start();
	
	_collision_system.add(_character->get());
}


void episode_game::stop()
{
	_collision_system.stop();
	
	_background.stop();
	
	_character->get()->stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::BG_1);
	asset_helper::getInstance().unload_texture(asset_helper::BG_2);
	
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
		// main character logic
		
		
		// enemies logic
		
		if(rand()%TIME_STEP>495)
		{
			add_enemies(1);
		}
		
		vector <enemy *>::iterator ite = _enemies.begin();
		while(ite!=_enemies.end())
		{
			enemy *obj = *(ite++);
			obj->update();
		}
		
		// character bullets logic
		while(_add_bullets>0)
		{
			bullet *obj = new bullet();
			obj->x_y(_character->get()->cx(),_character->get()->yh());
			obj->start();
			_bullets.push_back(obj);
			
			_collision_system.add(obj);
			
			_add_bullets--;
		}
		
		deque <bullet*>::iterator itb = _bullets.begin();
		while(itb!=_bullets.end())
		{
			bullet *obj = *(itb++);
			
			// is bullet dead
			if(obj->is_dead())
			{ 
				_collision_system.remove(obj);
				_bullets.erase(itb--);
				continue;
			}
			obj->update();
		}
		
		// enemies bullets logic
		
		// energy logic
		
		// bomb logic
		
		_last_clock = clock();
	}
	
	_character->get()->update();
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
	_character->get()->draw();
}


void episode_game::draw_enemies()
{
	vector <enemy *>::iterator it = _enemies.begin();
	while(it!=_enemies.end())
	{
		enemy *obj = *(it++);
		obj->draw();
	}
}


void episode_game::draw_bullets()
{
	deque <bullet*>::iterator it = _bullets.begin();
	while(it!=_bullets.end())
	{
		bullet *obj = *(it++);
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
		cout << "Collision! " << param.a << " - " << param.b << endl << flush;
		// bullet to enemy collision
		if( ( (param.a==TYPE_ENEMY) && (param.b==TYPE_BULLET) )
			|| ( (param.a==TYPE_BULLET) && (param.b==TYPE_ENEMY) ) )
		{
			cout << "Enemy dead!" << endl << flush;
		}
	}
}


/****************************************************************

							private

****************************************************************/


void episode_game::add_enemies(int batch)
{
	shared_ptr<enemy> object;
	return;
	
	unsigned int xmin = 50, xmax = 250;
	unsigned int ymin = 120, ymax = 140;
	
	for(int i=0;i<batch;i++)
	{
		unsigned int x = rand() % xmax + xmin;
		unsigned int y = rand() % ymax + ymin;
		
		enemy *object = new enemy();
		object->x_y(x,y);
		object->start();
		_enemies.push_back(object);
		_collision_system.add(object);
	}
}

