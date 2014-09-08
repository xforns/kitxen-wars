#ifndef EPISODE_SPLASH_H
#define EPISODE_SPLASH_H

#include <map>
#include <string>
#include <cstdio>
#include <ctime>

#include "gl_helper.h"
#include "episode.h"
#include "asset_helper.h"

using namespace std;

class episode_splash : public episode
{

private:
	
	enum _splash_episodes { SPLASH_EPISODE_COMPANY, SPLASH_EPISODE_PRESENTS, SPLASH_EPISODE_GAME };
	_splash_episodes _current_splash_episode;
	
	map<_splash_episodes,double> _episodes_timers;
	
	GLuint _current_bg;
	
	clock_t _start;
	
public:
	
	episode_splash();
	~episode_splash();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	
	// Starts the timer that governs the time showing each screen.
	void init_timer();
	
	// Returns whether the timer has expired.
	// Return:
	//	bool If true, timer has expired.
	bool timer_expired();
	
	// Loads an "episode": in the context of the splash, an episode means an image being displayed.
	// Params:
	//	episode Next image to load.
	void load_episode(_splash_episodes episode);
	
};

#endif /* EPISODE_SPLASH_H */