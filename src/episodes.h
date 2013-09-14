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

using namespace std;

class episodes : public observer
{
	
private:
	
	enum _episode_defs { SPLASH, MENU, GAME, HELP, END };
	
	_episode_defs _current_episode_def;
	
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
	void mouse(uint32_t status, int x, int y);
	
	virtual void update(int msg_type, const observable_data &param);
		 
};

#endif /* EPISODES_H */