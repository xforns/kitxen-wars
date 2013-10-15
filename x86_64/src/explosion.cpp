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
}


void explosion::update(const observable_data &param)
{
}

/****************************************************************

							private

****************************************************************/
