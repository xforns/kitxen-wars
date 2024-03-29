#include "bomb.h"


/****************************************************************

							public

****************************************************************/


bomb::bomb()
{
	_type = TYPE_BOMB;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::BOMB);
	
	_pos.x = 160.f;
	_pos.y = 50.f;
	
	_w = 40;
	_h = 40;
}


bomb::~bomb()
{
}


void bomb::start()
{
	_last_clock = clock();
}


void bomb::stop()
{
	asset_helper::getInstance().unload_texture(asset_helper::BOMB);
}

void bomb::update()
{
	double diff = clock() - _last_clock;
	if(diff>=TIME_STEP_BOMB)
	{
		if(_pos.x > 160)
		{
			_pos.x--;
		}
		else if(_pos.x < 160)
		{
			_pos.x++;
		}
		if(_pos.y > 100)
		{
			_pos.y--;
		}
		else if(_pos.y < 100)
		{
			_pos.y++;
		}
		
		_last_clock = clock();
	}
	
	if( (_pos.x==160) && (_pos.y==100) )
	{
		observable_data data;
		data.msg_type = MSG_BOMB;
		messaging::getInstance().notify(data);
	}
}


void bomb::draw()
{
	gl_helper::draw_texture(_bg,_pos.x,_pos.y,0,0,40,40);
}


/****************************************************************

						observer interface

****************************************************************/


void bomb::update(const observable_data &param)
{
}


/****************************************************************

							private

****************************************************************/
