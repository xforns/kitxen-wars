#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <OpenGL/OpenGL.h>

#include <cstdio>
#include <ctime>

#include "entity.h"
#include "defs.h"
#include "asset_helper.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class explosion : public entity, public observer 
{

private:
	
	GLuint _bg;
	
	clock_t _last_clock;
	
	bool _is_dead;
	
public:
	
	explosion();
	virtual ~explosion();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(const observable_data &param);
};

#endif /* EXPLOSION_H */