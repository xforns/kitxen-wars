#ifndef BULLET_H
#define BULLET_H

#include <OpenGL/OpenGL.h>

#include "entity.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class bullet : public entity, public observer 
{

private:
	
	GLuint _bg;
	bool _die;
	
public:
	
	bullet();
	virtual ~bullet();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(const observable_data &param);
	
	bool is_dead();
	void set_dead();
	
};

#endif /* BULLET_H */