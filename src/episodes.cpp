#include "episodes.h"


/****************************************************************

							public

****************************************************************/


episodes::episodes()
{
}


episodes::~episodes()
{
	
}


void episodes::start()
{
	_current_status = STATUS_PLAYING;
	
	messaging::getInstance().add(this);
	
	// load initial episode
	//load(SPLASH);
	_next_episode = SPLASH;
	load(MENU);
}


void episodes::glutDisplayFunc()
{
	update();
	draw();
}


void episodes::glutReshapeFunc(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}


bool episodes::hasFinished()
{
	return _current_status==STATUS_END;
}


/****************************************************************

						observer interface

****************************************************************/


void episodes::update(const observable_data &param)
{
	// episode change
	if(param.msg_type==MSG_EPISODE)
	{
		// menu
		if(param.a==EPISODE_MENU)
		{
			_next_episode = MENU;
		}
		// game
		else if(param.a==EPISODE_GAME)
		{
			_next_episode = GAME;
		}
		// game over
		else if(param.a==EPISODE_GAMEOVER)
		{
			
		}
		// help
		else if(param.a==EPISODE_HELP)
		{
			_next_episode = HELP;
		}
		// exit
		else if(param.a==EPISODE_EXIT)
		{
			_current_episode->stop();
			delete _current_episode;
			
			_current_status = STATUS_END;
		}
	}
}

/****************************************************************

							private

****************************************************************/

void episodes::update()
{
	// change episode
	if(_current_episode->get_episode_status()==episode::ENDED)
	{
		if(_current_episode_def==SPLASH)
		{
			_next_episode = MENU;
		}
	}
	
	if(_current_episode_def!=_next_episode)
	{
		load(_next_episode);
	}
	
	_current_episode->update();
}


void episodes::draw()
{
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0.0, 320.0, 0.0, 200, -1.0, 1.0);
	
	_current_episode->draw();
	
	glFlush();
}


bool episodes::load(_episode_defs episode)
{
	_current_episode_def = episode;
	
	// stop current episode
	if(_current_episode!=NULL)
	{
		_current_episode->stop();
		
		delete _current_episode;
	}
	
	// load new episode
	if(_current_episode_def==SPLASH)
	{
		_current_episode = new episode_splash();
	}
	else if(_current_episode_def==MENU)
	{
		_current_episode = new episode_menu();
	}
	else if(_current_episode_def==HELP)
	{
		_current_episode = new episode_help();
	}
	else if(_current_episode_def==GAME)
	{
		_current_episode = new episode_game();
	}
	
	_current_episode->start();
	
	return true;
}
