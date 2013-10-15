#ifndef ENEMY_H
#define ENEMY_H

#include <OpenGL/OpenGL.h>
#include <ctime>
#include <cstdio>

#include "entity.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class enemy : public entity, public observer 
{

private:
	
	GLuint _bg;
	clock_t _last_clock;
	
public:
	
	enemy();
	virtual ~enemy();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(const observable_data &param);
	
};

#endif /* ENEMY_H */