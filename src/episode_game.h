#ifndef EPISODE_GAME_H
#define EPISODE_GAME_H

#include <OpenGL/OpenGL.h>
#include <deque>
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
#include "character.h"
#include "bullet.h"
#include "collision_system.h"

using namespace std;

class episode_game : public episode, public observer
{

private:
	
	GLuint _bg1, _bg2;
	
	clock_t _last_clock;
	
	double _bg_y1, _bg_y2;
	
	character _character;
	
	deque <bullet*> _bullets;
	
	unsigned int _add_bullets;
	
	void draw_bg();
	void draw_main_character();
	void draw_enemies();
	void draw_bullets();
	
public:
	
	episode_game();
	~episode_game();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	
	virtual void update(const observable_data &param);
	
};

#endif /* EPISODE_GAME_H */