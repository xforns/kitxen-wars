#include "bullet.h"

/****************************************************************

							public

****************************************************************/


bullet::bullet()
{
	_type = TYPE_BULLET;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::BULLET);
	
	_pos.x = 160.f;
	_pos.y = 50.f;
	
	_w = 4;
	_h = 8;
}


bullet::~bullet()
{
}


void bullet::start()
{
	messaging::getInstance().add(this);
}


void bullet::stop()
{
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::BULLET);
}

void bullet::update()
{
	_pos.y += 1;
}


void bullet::draw()
{
	gl_helper::draw_texture(_bg,_pos.x,_pos.y,0,0,4,8);
}


/****************************************************************

						observer interface

****************************************************************/


void bullet::update(const observable_data &param)
{
	// bounds check
	if( (param.msg_type==MSG_COLLISION) && (param.a==TYPE_BULLET) && (param.b==TYPE_NONE) )
	{
		if(param.c==COLLISION_TOP)
		{
			_dead = true;
		}
	}
	
}


/****************************************************************

							private

****************************************************************/
