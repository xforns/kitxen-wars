#ifndef EPISODE_GAME_H
#define EPISODE_GAME_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>

#include "gl_helper.h"
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
#include "bomb.h"
#include "energy.h"
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
	bomb *_bomb;
	energy *_energy;
	
	
	bool _add_bomb;
	bool _kill_all_enemies;
	bool _kill_all_enemies_enable;
	
	unsigned int _add_bullets;
	
	collision_system _collision_system;
	
	// Draws the main character.
	void draw_main_character();
	
	// Draw all enemies.
	void draw_enemies();
	
	// Draws all bullets.
	void draw_bullets();
	
	// Adds enemies, as many as indicated.
	// Params:
	//	batch: Number of enemies to add.
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