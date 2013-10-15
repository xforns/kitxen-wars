#include "enemy.h"


/****************************************************************

							public

****************************************************************/


enemy::enemy()
{
	_type = TYPE_ENEMY;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::ENEMY);
	
	_w = 40;
	_h = 40;
}


enemy::~enemy()
{
}


void enemy::start()
{
	messaging::getInstance().add(this);
}


void enemy::stop()
{
	messaging::getInstance().remove(this);
}

void enemy::update()
{
	_pos.y += rand()%100+1 > 99.5 ? -1 : 0;
}


void enemy::draw()
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


void enemy::update(const observable_data &param)
{
	if(param.msg_type==MSG_COLLISION)
	{
		double diff = clock() - _last_clock;
		if(diff<TIME_STEP_ENEMY_COLLISION)
		{
			return;
		}
		
		// bounds check
		if( (param.a==TYPE_ENEMY) && (param.b==TYPE_NONE) )
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
		// enemy to enemy collision
		else if( (param.a==TYPE_ENEMY) && (param.b==TYPE_ENEMY) )
		{
			shared_ptr<enemy> ptr1 = dynamic_pointer_cast<enemy>(param.o1);
			shared_ptr<enemy> ptr2 = dynamic_pointer_cast<enemy>(param.o2);
			
			int direction = ptr1.get()==this ? 1 : -1;
			
			if(param.c==COLLISION_LEFT)
			{
				_pos.x += 1*direction;
			}
			else if(param.c==COLLISION_RIGHT)
			{
				_pos.x -= 1*direction;
			}
			else if(param.c==COLLISION_TOP)
			{
				_pos.y += 1*direction;
			}
			else if(param.c==COLLISION_BOTTOM)
			{
				_pos.y -= 1*direction;
			}
		}
		
		_last_clock = clock();
	}
}


/****************************************************************

							private

****************************************************************/
