#include "explosion.h"

/****************************************************************

							public

****************************************************************/


explosion::explosion()
{
	_type = TYPE_EXPLOSION;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::EXPLOSION);
}


explosion::~explosion()
{
}


void explosion::start()
{
	_last_clock = clock();
	
	_dead = false;
}


void explosion::stop()
{
}

void explosion::update()
{
	double diff = clock()-_last_clock;
	if(diff>=TIME_EXPLOSION_DURATION)
	{
		_dead = true;
	}
}


void explosion::draw()
{
	if(!_dead)
	{
		gl_helper::draw_texture(_bg,_pos.x,_pos.y,0,0,40,40);
	}
}


void explosion::update(const observable_data &param)
{
}

/****************************************************************

							private

****************************************************************/
