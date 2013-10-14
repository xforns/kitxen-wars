#include "enemy.h"


/****************************************************************

							public

****************************************************************/


enemy::enemy()
{
	_type = TYPE_ENEMY;
	
	_bg = asset_helper::getInstance().get_texture(asset_helper::ENEMY);
	id = rand()%1000 + 1;
	cout << "created enemy: " << id << endl << flush;
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
}


/****************************************************************

							private

****************************************************************/
