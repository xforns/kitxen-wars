#include "character.h"
#include "gl_helper.h"

/****************************************************************

							public

****************************************************************/


character::character()
{
	_type = TYPE_CHARACTER;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::CHARACTER);
	
	_pos.x = 160.f;
	_pos.y = 50.f;
	
	_w = 40;
	_h = 40;
}


character::~character()
{
}


void character::start()
{
	messaging::getInstance().add(this);
}


void character::stop()
{
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::CHARACTER);
}

void character::update()
{
}


void character::draw()
{
	gl_helper::draw_texture(_bg,_pos.x,_pos.y,0,0,40,40);
}


/****************************************************************

						observer interface

****************************************************************/


void character::update(const observable_data &param)
{
	if(param.msg_type==MSG_KEYBOARD_S)
	{
		switch(param.a)
		{
			// left
			case 100:
				_pos.x -= 8;
				break;
			// right
			case 102:
				_pos.x += 8;
				break;
			// down
			case 103:
				_pos.y -= 4;
				break;
			// up
			case 101:
				_pos.y += 4;
				break;
		}
	}
	// collisions
	else if(param.msg_type==MSG_COLLISION)
	{
		// bounds check
		if( (param.a==TYPE_CHARACTER) && (param.b==TYPE_NONE) )
		{
			if(param.c==COLLISION_LEFT)
			{
				_pos.x++;
			}
			else if(param.c==COLLISION_RIGHT)
			{
				_pos.x--;
			}
			else if(param.c==COLLISION_TOP)
			{
				_pos.y--;
			}
			else if(param.c==COLLISION_BOTTOM)
			{
				_pos.y++;
			}
		}
		// enemy collision
		else if( ( (param.a==TYPE_CHARACTER) && (param.b==TYPE_ENEMY) )
			|| ( (param.a==TYPE_ENEMY) && (param.b==TYPE_CHARACTER) ) )
		{
			_dead = true;
		}
	}
}


/****************************************************************

							private

****************************************************************/
