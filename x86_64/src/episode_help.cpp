#include "episode_help.h"
#include "defs.h"
#include "gl_helper.h"
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
	
	gl_helper::draw_texture(_bg,0.f,0.f,0,0,320,200);
}


/****************************************************************

						observer interface

****************************************************************/


void episode_help::update(const observable_data &param)
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


