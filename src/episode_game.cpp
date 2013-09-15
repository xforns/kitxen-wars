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
	
	_char = asset_helper::getInstance().get_texture(asset_helper::CHARACTER);
	
	_pt_char.x = 160.f;
	_pt_char.y = 50.f;
	
	_last_clock = clock();
}


void episode_game::stop()
{
	episode::stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::HELP);
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
		
		
		// enemies bullets logic
		
		// energy logic
		
		// bomb logic
		
		_last_clock = clock();
	}
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
	glPushMatrix();
	
	glTranslatef(_pt_char.x,_pt_char.y,0.f);
	
	glBindTexture(GL_TEXTURE_2D,_char);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(40,40);	// top right
    glTexCoord2i(1,0); glVertex2i(40,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,40);	// top left
	glEnd();
	
	glPopMatrix();
}


void episode_game::draw_enemies()
{
	
}


/****************************************************************

						observer interface

****************************************************************/


void episode_game::update(int msg_type, const observable_data &param)
{
	if(msg_type==MSG_MOUSE)
	{
		if(param.a==LMB_PRESSED)
		{
			observable_data data;
			data.a = EPISODE_MENU;
			messaging::getInstance().notify(MSG_EPISODE,data);
		}
	}
}


/****************************************************************

							private

****************************************************************/


