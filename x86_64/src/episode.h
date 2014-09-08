#ifndef EPISODE_H
#define EPISODE_H

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
	
	// Following methods are virtual, possibly used by derived classes
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual _episode_status get_episode_status();
	
	// Following 2 methods are pure virtual, derived classes need to implement them
	
	virtual void update()=0;
	virtual void draw()=0;
	
};

#endif /* EPISODE_H */