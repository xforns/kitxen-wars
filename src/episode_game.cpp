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
	
	_bg1 = asset_helper::getInstance().get_texture(asset_helper::BG_1);
	_bg2 = asset_helper::getInstance().get_texture(asset_helper::BG_2);
	
	_bg_y1 = 0.f;
	_bg_y2 = 200.f;
	
	_add_bullets = 0;
	
	_last_clock = clock();
	
	_character.start();
}


void episode_game::stop()
{
	_character.stop();
	
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
		// background logic
		_bg_y1 = _bg_y1<=-200.f ? 200.f : _bg_y1-1;
		_bg_y2 = _bg_y2<=-200.f ? 200.f : _bg_y2-1;
		
		// main character logic
		
		
		// enemies logic
		
		
		// character bullets logic
		while(_add_bullets>0)
		{
			bullet *obj = new bullet();
			obj->x(_character.cx());
			obj->y(_character.yh());
			obj->start();
			_bullets.push_back(obj);
			
			_add_bullets--;
		}
		
		deque <bullet*>::iterator it = _bullets.begin();
		while(it!=_bullets.end())
		{
			bullet *obj = *(it++);
			obj->update();
		}
		
		// enemies bullets logic
		
		// energy logic
		
		// bomb logic
		
		_last_clock = clock();
	}
	
	_character.update();
}


void episode_game::draw()
{
    glColor3f(1.f,1.f,1.f);
	
    draw_bg();
	
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
	
    draw_enemies();
	
	draw_main_character();
	
	draw_bullets();
	
	glDisable(GL_BLEND);
}


void episode_game::draw_bg()
{
	// bg 2
	
	glPushMatrix();
	
	glTranslatef(0.f,_bg_y2,0.f);
	
    glBindTexture(GL_TEXTURE_2D,_bg2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
	
	glPopMatrix();
	
	// bg 1
	
	glPushMatrix();
	
	glTranslatef(0.f,_bg_y1,0.f);
	
    glBindTexture(GL_TEXTURE_2D,_bg1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
	
	glPopMatrix();
}


void episode_game::draw_main_character()
{
	_character.draw();
}


void episode_game::draw_enemies()
{
	
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
			std::cout << "Adding new bullet" << std::endl << std::flush;
			_add_bullets++;
		}
	}
}


/****************************************************************

							private

****************************************************************/


