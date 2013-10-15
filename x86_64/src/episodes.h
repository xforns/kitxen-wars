#ifndef EPISODES_H
#define EPISODES_H

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <map>
#include <string>
#include <iostream>

#include "defs.h"
#include "observer.h"
#include "messaging.h"
#include "episode.h"
#include "episode_splash.h"
#include "episode_menu.h"
#include "episode_help.h"
#include "episode_game.h"
#include "episode_end.h"

using namespace std;

class episodes : public observer
{
	
private:
	
	enum _episode_defs { SPLASH, MENU, GAME, HELP, GAME_OVER };
	enum _status { STATUS_PLAYING, STATUS_END };
	
	_status _current_status;
	
	_episode_defs _current_episode_def;
	_episode_defs _next_episode;
	
	episode *_current_episode;
	
	void update();
 	void draw();
	bool load(_episode_defs episode);
 
public:
		 
	episodes();
	~episodes();
	
	void start();
	void glutDisplayFunc();
	void glutReshapeFunc(int w, int h);
	
	bool hasFinished();
	
	virtual void update(const observable_data &param);
		 
};

#endif /* EPISODES_H */