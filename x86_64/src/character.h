#ifndef CHARACTER_H
#define CHARACTER_H

#include "gl_helper.h"
#include "entity.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class character : public entity, public observer 
{

private:
	
	GLuint _bg;
	
public:
	
	character();
	virtual ~character();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(const observable_data &param);
	
};

#endif /* CHARACTER_H */