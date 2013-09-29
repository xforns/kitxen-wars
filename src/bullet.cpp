#include "bullet.h"


/****************************************************************

							public

****************************************************************/


bullet::bullet()
{
	_type = TYPE_CHARACTER;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::BULLET);
	
	_pos.x = 160.f;
	_pos.y = 50.f;
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
	glPushMatrix();
	
	glTranslatef(_pos.x,_pos.y,0.f);
	
	glBindTexture(GL_TEXTURE_2D,_bg);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(4,8);	// top right
    glTexCoord2i(1,0); glVertex2i(4,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);	// bottom left
    glTexCoord2i(0,1); glVertex2i(0,8);	// top left
	glEnd();
	
	glPopMatrix();
}


/****************************************************************

						observer interface

****************************************************************/


void bullet::update(const observable_data &param)
{
}


/****************************************************************

							private

****************************************************************/
