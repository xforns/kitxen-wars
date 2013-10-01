#ifndef EPISODE_H
#define EPISODE_H

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <map>
#include <string>
//#include "asset_helper.h"

using namespace std;

class episode
{
public:
	
	enum _episode_defs { SPLASH, MENU, GAME, END };
	enum _episode_status { NOT_INITIALIZED, PLAYING, PAUSED, ENDED };
	
	_episode_defs _current_episode_def;
	_episode_status _current_episode_status;
	
	episode();
	virtual ~episode();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update()=0;
	virtual void draw()=0;
	virtual _episode_status get_episode_status();
	
};

#endif /* EPISODE_H */