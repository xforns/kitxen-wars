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
	
	gl_helper::draw_texture(_bg,0.f,0.f,0,0,320,200);
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


