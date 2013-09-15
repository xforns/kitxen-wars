#ifndef EPISODE_GAME_H
#define EPISODE_GAME_H

#include <OpenGL/OpenGL.h>
#include <map>
#include <string>
#include <cstdio>
#include <ctime>
#include <iostream>

#include "episode.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class episode_game : public episode, public observer
{

private:
	
	GLuint _bg1, _bg2;
	
	GLuint _char;
	
	clock_t _last_clock;
	
	double _bg_y1, _bg_y2;
	
	pt _pt_char;
	
	void draw_bg();
	void draw_main_character();
	void draw_enemies();
	
public:
	
	episode_game();
	~episode_game();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	
	virtual void update(int msg_type, const observable_data &param);
	
};

#endif /* EPISODE_GAME_H */