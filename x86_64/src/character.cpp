#include "character.h"


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
	glPushMatrix();
	
	glTranslatef(_pos.x,_pos.y,0.f);
	
	glBindTexture(GL_TEXTURE_2D,_bg);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(40,40);	// top right
    glTexCoord2i(1,0); glVertex2i(40,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,40);	// top left
	glEnd();
	
	glPopMatrix();
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
			|| (param.a==TYPE_ENEMY) && (param.b==TYPE_CHARACTER) )
		{
			_dead = true;
		}
	}
}


/****************************************************************

							private

****************************************************************/
