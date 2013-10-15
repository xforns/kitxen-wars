#ifndef EPISODE_GAME_H
#define EPISODE_GAME_H

#include <OpenGL/OpenGL.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>

#include "episode.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"
#include "background_game.h"
#include "character.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "collision_system.h"

using namespace std;

class episode_game : public episode, public observer
{

private:
	
	typedef shared_ptr<bullet> bullet_ptr;
	typedef shared_ptr<character> character_ptr;
	typedef shared_ptr<enemy> enemy_ptr;
	typedef shared_ptr<entity> entity_ptr;
	
	background_game _background;
	
	character_ptr _character;
	vector <bullet_ptr> _bullets;
	vector <enemy_ptr> _enemies;
	vector <explosion *> _explosions;
	explosion *_character_explosion;
	
	unsigned int _add_bullets;
	
	collision_system _collision_system;
	
	void draw_main_character();
	void draw_enemies();
	void draw_bullets();
	
	void add_enemies(int batch);
	
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