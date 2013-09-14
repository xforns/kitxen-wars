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
	
	messaging::getInstance().add(this);
	
	// load initial episode
	load(SPLASH);
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


void episodes::mouse(uint32_t status, int x, int y)
{
	_current_episode->mouse(status,x,y);
}


/****************************************************************

						observer interface

****************************************************************/


void episodes::update(int msg_type, const observable_data &param)
{
	// episode change
	if(msg_type==MSG_EPISODE)
	{
		// menu
		if(param.a==EPISODE_MENU)
		{
			load(MENU);
		}
		// game
		else if(param.a==EPISODE_GAME)
		{
			load(GAME);
		}
		// game over
		else if(param.a==EPISODE_GAMEOVER)
		{
			
		}
		// help
		else if(param.a==EPISODE_HELP)
		{
			load(HELP);
		}
		// exit
		else if(param.a==EPISODE_EXIT)
		{
			exit(1);
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
			load(MENU);
		}
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
	
	_current_episode->start();
	
	return true;
}
