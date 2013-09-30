#include "episode_menu.h"
#include "defs.h"
#include <iostream>

/****************************************************************

							public

****************************************************************/


episode_menu::episode_menu()
{
}


episode_menu::~episode_menu()
{
	
}


void episode_menu::start()
{
	episode::start();
	
	messaging::getInstance().add(this);
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::MENU);
}


void episode_menu::stop()
{
	episode::stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::MENU);
}


void episode_menu::pause()
{
	episode::pause();
}


void episode_menu::update()
{
}


void episode_menu::draw()
{
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D,_bg);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	

    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
}


/****************************************************************

						observer interface

****************************************************************/


void episode_menu::update(const observable_data &param)
{
	// check for pressed options:
	if(param.msg_type==MSG_MOUSE)
	{
		if(param.a==LMB_PRESSED)
		{
			int x = param.b;
			int y = param.c;
			
			// game
			if( (x>=324) && (x<=417) && (y>=152) && (y<=198) )
			{
				observable_data data;
				data.msg_type = MSG_EPISODE;
				data.a = EPISODE_GAME;
				messaging::getInstance().notify(data);
			}
			// help
			else if( (x>=324) && (x<=417) && (y>=265) && (y<=308) )
			{
				observable_data data;
				data.msg_type = MSG_EPISODE;
				data.a = EPISODE_HELP;
				messaging::getInstance().notify(data);
			}
			// exit
			else if( (x>=324) && (x<=417) && (y>=380) && (y<=425) )
			{
				observable_data data;
				data.msg_type = MSG_EPISODE;
				data.a = EPISODE_EXIT;
				messaging::getInstance().notify(data);
			}
		}
	}
}


/****************************************************************

							private

****************************************************************/


