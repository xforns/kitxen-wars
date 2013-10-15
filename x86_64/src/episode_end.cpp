#include "episode_end.h"
#include "defs.h"
#include <iostream>

/****************************************************************

							public

****************************************************************/


episode_end::episode_end()
{
}


episode_end::~episode_end()
{
	
}


void episode_end::start()
{
	episode::start();
	
	messaging::getInstance().add(this);
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::GAME_OVER);
	
	_last_clock = clock();
}


void episode_end::stop()
{
	episode::stop();
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::GAME_OVER);
}


void episode_end::pause()
{
	episode::pause();
}


void episode_end::update()
{
	double diff = clock() - _last_clock;
	if(diff>=TIME_GAME_OVER)
	{
		_current_episode_status = ENDED;
	}
}


void episode_end::draw()
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


void episode_end::update(const observable_data &param)
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


