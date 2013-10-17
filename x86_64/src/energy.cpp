#include "energy.h"


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
	glPushMatrix();
	
	glTranslatef(_pos.x,_pos.y,0.f);
	
	glBindTexture(GL_TEXTURE_2D,_bg);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(120,20);
    glTexCoord2i(1,0); glVertex2i(120,0);
    glTexCoord2i(0,0); glVertex2i(0,0);
    glTexCoord2i(0,1); glVertex2i(0,20);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPushMatrix();
	
	glTranslatef(38.f,0.f,0.f);
	glLineWidth(1.f);
	glColor3f(0.f,1.f,0.f);
	
    glBegin(GL_QUADS);
    glVertex2i(_en,18);
    glVertex2i(_en,2);
    glVertex2i(0,2);
    glVertex2i(0,18);
	glEnd();
	
	glPopMatrix();
	
	glPopMatrix();
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
