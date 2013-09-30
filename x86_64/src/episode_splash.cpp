#include "episode_splash.h"


/****************************************************************

							public

****************************************************************/


episode_splash::episode_splash()
{
	_episodes_timers = map<_splash_episodes,double>();
	_episodes_timers.insert( pair<_splash_episodes,double>(SPLASH_EPISODE_COMPANY,0.2) );
	_episodes_timers.insert( pair<_splash_episodes,double>(SPLASH_EPISODE_PRESENTS,0.2) );
	_episodes_timers.insert( pair<_splash_episodes,double>(SPLASH_EPISODE_GAME,0.2) );
	
	_current_episode_status = NOT_INITIALIZED;
}


episode_splash::~episode_splash()
{
	
}


void episode_splash::start()
{
	episode::start();
	
	load_episode(SPLASH_EPISODE_COMPANY);
}


void episode_splash::stop()
{
	episode::stop();
	
	// unload last episode
	asset_helper::getInstance().unload_texture(asset_helper::SPLASH_GAME);
}


void episode_splash::pause()
{
	episode::pause();
}


void episode_splash::update()
{
	// timer expired: change screen
	if(timer_expired())
	{
		if(_current_splash_episode==SPLASH_EPISODE_COMPANY)
		{
			load_episode(SPLASH_EPISODE_PRESENTS);
		}
		else if(_current_splash_episode==SPLASH_EPISODE_PRESENTS)
		{
			load_episode(SPLASH_EPISODE_GAME);
		}
		else if(_current_splash_episode==SPLASH_EPISODE_GAME)
		{
			stop();
		}
	}
}


void episode_splash::draw()
{
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D,_current_bg);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	

    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(320,200);	// top right
    glTexCoord2i(1,0); glVertex2i(320,0);	// bottom right
    glTexCoord2i(0,0); glVertex2i(0,0);		// bottom left
    glTexCoord2i(0,1); glVertex2i(0,200);	// top left
	glEnd();
}


/****************************************************************

							private

****************************************************************/


void episode_splash::load_episode(_splash_episodes episode)
{
	// company splash
	if(episode==SPLASH_EPISODE_COMPANY)
	{
		_current_bg = asset_helper::getInstance().get_texture(asset_helper::SPLASH_COMPANY);
	}
	// presents splash
	else if(episode==SPLASH_EPISODE_PRESENTS)
	{
		_current_bg = asset_helper::getInstance().get_texture(asset_helper::SPLASH_PRESENTS);
		
		asset_helper::getInstance().unload_texture(asset_helper::SPLASH_COMPANY);
	}
	// game splash
	else if(episode==SPLASH_EPISODE_GAME)
	{
		_current_bg = asset_helper::getInstance().get_texture(asset_helper::SPLASH_GAME);
		
		asset_helper::getInstance().unload_texture(asset_helper::SPLASH_PRESENTS);
	}
	
	_current_splash_episode = episode;
	
	init_timer();
	
}


void episode_splash::init_timer()
{
	_start = clock();
}


bool episode_splash::timer_expired()
{
    double duration = ( clock() - _start ) / (double) CLOCKS_PER_SEC;
	return duration>=_episodes_timers[_current_splash_episode];
}

