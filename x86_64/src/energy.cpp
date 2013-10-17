#include "energy.h"
#include "gl_helper.h"

/****************************************************************

							public

****************************************************************/


energy::energy()
{
	_bg = asset_helper::getInstance().get_texture(asset_helper::ENERGY);
	
	_pos.x = 195.f;
	_pos.y = 175.f;
	
	_w = 180;
	_h = 160;
	
	_en = 0;
}

energy::~energy()
{
}


void energy::start()
{
	messaging::getInstance().add(this);
}


void energy::stop()
{
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::ENERGY);
}


void energy::update()
{
	if(_en>=82)
	{
		observable_data data;
		data.msg_type = MSG_BOMB_ENABLE;
		messaging::getInstance().notify(data);
			
		_en = 0;
	}
}


void energy::draw()
{
	gl_helper::draw_texture(_bg,_pos.x,_pos.y,0,0,120,20);
	gl_helper::draw_quad(_pos.x+38.f,_pos.y,0,2,_en,18,_energy_color);
}


void energy::update(const observable_data &param)
{
	// collisions
	if(param.msg_type==MSG_COLLISION)
	{
		// bounds check
		if( ( (param.a==TYPE_ENEMY) && (param.b==TYPE_BULLET) )
			|| ( (param.a==TYPE_BULLET) && (param.b==TYPE_ENEMY) ) )
		{
			_en += 2;
 		}
	}
}


/****************************************************************

							private

****************************************************************/
