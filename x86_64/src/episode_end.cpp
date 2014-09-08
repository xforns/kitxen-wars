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
	
	gl_helper::draw_texture(_bg,0.f,0.f,0,0,320,200);
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


