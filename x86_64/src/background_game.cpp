#include "background_game.h"

GLuint background_game::_bg1, background_game::_bg2;
double background_game::_bg_y1, background_game::_bg_y2;
clock_t background_game::_last_clock;
bool background_game::_cancel_thread;

/****************************************************************

							public

****************************************************************/


background_game::background_game()
{

	_bg1 = asset_helper::getInstance().get_texture(asset_helper::BG_1);
	_bg2 = asset_helper::getInstance().get_texture(asset_helper::BG_2);
	
	_bg_y1 = 0.f;
	_bg_y2 = 200.f;
}


background_game::~background_game()
{
}


void background_game::start()
{
	messaging::getInstance().add(this);
	
	_last_clock = clock();
	
	_cancel_thread = false;
	
	pthread_create(&thread,NULL,&t_update,NULL);
}


void background_game::stop()
{
	_cancel_thread = true;
	
	messaging::getInstance().remove(this);
	
	asset_helper::getInstance().unload_texture(asset_helper::BG_1);
	asset_helper::getInstance().unload_texture(asset_helper::BG_2);
}


void *background_game::t_update(void *)
{
	while(true)
	{
		double diff = ( clock() - _last_clock );
		if(diff>=TIME_STEP_BG)
		{
			_bg_y1 = _bg_y1<=-200.f ? 200.f : _bg_y1-1;
			_bg_y2 = _bg_y2<=-200.f ? 200.f : _bg_y2-1;
		
			_last_clock = clock();
		}
	
		if(_cancel_thread)
		{
			pthread_exit(NULL);
		}
	}
}


void background_game::draw()
{
    // bg 2
	
	glPushMatrix();
	
	glTranslatef(0.f,_bg_y2,0.f);
	
    glBindTexture(GL_TEXTURE_2D,_bg2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
	
	glPopMatrix();
	
	// bg 1
	
	glPushMatrix();
	
	glTranslatef(0.f,_bg_y1,0.f);
	
    glBindTexture(GL_TEXTURE_2D,_bg1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	
	
    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
	
	glPopMatrix();
}


/****************************************************************

						observer interface

****************************************************************/


void background_game::update(const observable_data &param)
{
}


/****************************************************************

							private

****************************************************************/
