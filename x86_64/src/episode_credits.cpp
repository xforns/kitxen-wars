#include "episode_credits.h"
#include "defs.h"
#include "gl_helper.h"
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
	
	gl_helper::draw_texture(_bg,0.f,0.f,0,0,320,200);
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


