#ifndef BOMB_H
#define BOMB_H

#include <OpenGL/OpenGL.h>
#include <ctime>
#include <cstdio>

#include "gl_helper.h"
#include "entity.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class bomb : public entity, public observer 
{

private:
	
	GLuint _bg;
	
	clock_t _last_clock;
	
public:
	
	bomb();
	virtual ~bomb();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(const observable_data &param);
	
};

#endif /* BOMB_H */