#ifndef EPISODES_H
#define EPISODES_H

#include <map>
#include <string>
#include <iostream>

#include "gl_helper.h"
#include "defs.h"
#include "observer.h"
#include "messaging.h"
#include "episode.h"
#include "episode_splash.h"
#include "episode_menu.h"
#include "episode_help.h"
#include "episode_game.h"
#include "episode_end.h"
#include "episode_credits.h"

using namespace std;

class episodes : public observer
{
	
private:
	
	enum _episode_defs { SPLASH, MENU, GAME, HELP, GAME_OVER, END_GAME };
	enum _status { STATUS_PLAYING, STATUS_END };
	
	_status _current_status;
	
	_episode_defs _current_episode_def;
	_episode_defs _next_episode;
	
	episode *_current_episode;
	
	// Update routine.
	void update();
	
	// Draw routine.
 	void draw();
	
	// Loads an episode.
	// Params:
	//	episode: Episode to load.
	bool load(_episode_defs episode);
 
public:
		 
	episodes();
	~episodes();
	
	// Convenience function for initialization purposes.
	void start();
	
	// Convenience function taking the same name as its GLUT counterpart.
	void glutDisplayFunc();
	
	// Convenience function taking the same name as its GLUT counterpart.
	void glutReshapeFunc(int w, int h);
	
	// Returns whether the whole game has finished, that is, user wants to exit from the menu.
	// Return:
	//	bool True if game has to stop.
	bool hasFinished();
	
	virtual void update(const observable_data &param);
		 
};

#endif /* EPISODES_H */