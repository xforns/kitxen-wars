#include "background_game.h"

GLuint background_game::_bg1, background_game::_bg2;
double background_game::_bg_y1, background_game::_bg_y2;
clock_t background_game::_last_clock;
bool background_game::_cancel_thread;

/****************************************************************

							public

****************************************************************/


background_game::background_game()
{

	_bg1 = asset_helper::getInstance().get_texture(asset_helper::BG_1);
	_bg2 = asset_helper::getInstance().get_texture(asset_helper::BG_2);
	
	_bg_y1 = 0.f;
	_bg_y2 = 200.f;
}


background_game::~background_game()
{
}


void background_game::start()
{
	messaging::getInstance().add(this);
	
	_last_clock = clock();
	
	_cancel_thread = false;
	
	pthread_create(&thread,NULL,&t_update,NULL);
}


void background_game::stop()
{
	_cancel_thread = true;
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::BG_1);
	asset_helper::getInstance().unload_texture(asset_helper::BG_2);
}


void *background_game::t_update(void *)
{
	while(true)
	{
		double diff = ( clock() - _last_clock );
		if(diff>=TIME_STEP_BG)
		{
			_bg_y1 = _bg_y1<=-200.f ? 200.f : _bg_y1-1;
			_bg_y2 = _bg_y2<=-200.f ? 200.f : _bg_y2-1;
		
			_last_clock = clock();
		}
	
		if(_cancel_thread)
		{
			pthread_exit(NULL);
		}
	}
}


void background_game::draw()
{
    // bg 2
	gl_helper::draw_texture(_bg2,0.f,_bg_y2,0,0,320,200);
	
	// bg 1
	gl_helper::draw_texture(_bg1,0.f,_bg_y1,0,0,320,200);
}


/****************************************************************

						observer interface

****************************************************************/


void background_game::update(const observable_data &param)
{
}


/****************************************************************

							private

****************************************************************/
