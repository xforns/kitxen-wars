#ifndef EPISODE_SPLASH_H
#define EPISODE_SPLASH_H

#include <OpenGL/OpenGL.h>
#include <map>
#include <string>
#include <cstdio>
#include <ctime>

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
	
	void init_timer();
	bool timer_expired();
	void load_episode(_splash_episodes episode);
};

#endif /* EPISODE_SPLASH_H */