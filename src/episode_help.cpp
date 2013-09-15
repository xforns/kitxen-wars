#include "episode_help.h"
#include "defs.h"
#include <iostream>

/****************************************************************

							public

****************************************************************/


episode_help::episode_help()
{
}


episode_help::~episode_help()
{
	
}


void episode_help::start()
{
	episode::start();
	
	messaging::getInstance().add(this);
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::HELP);
}


void episode_help::stop()
{
	episode::stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::HELP);
}


void episode_help::pause()
{
	episode::pause();
}


void episode_help::update()
{
}


void episode_help::draw()
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


void episode_help::update(int msg_type, const observable_data &param)
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


