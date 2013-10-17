#include "episode_credits.h"
#include "defs.h"
#include <iostream>

/****************************************************************

							public

****************************************************************/


episode_credits::episode_credits()
{
}


episode_credits::~episode_credits()
{
	
}


void episode_credits::start()
{
	episode::start();
	
	messaging::getInstance().add(this);
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::END_GAME);
	
	_last_clock = clock();
}


void episode_credits::stop()
{
	episode::stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::END_GAME);
}


void episode_credits::pause()
{
	episode::pause();
}


void episode_credits::update()
{
	double diff = clock() - _last_clock;
	if(diff>=TIME_GAME_END)
	{
		_current_episode_status = ENDED;
	}
}


void episode_credits::draw()
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


void episode_credits::update(const observable_data &param)
{
	if(param.msg_type==MSG_MOUSE)
	{
		if(param.a==LMB_PRESSED)
		{
			observable_data data;
			data.msg_type = MSG_EPISODE;
			data.a = EPISODE_MENU;
			messaging::getInstance().notify(data);
		}
	}
}


/****************************************************************

							private

****************************************************************/


