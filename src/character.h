#ifndef CHARACTER_H
#define CHARACTER_H

#include <OpenGL/OpenGL.h>

#include "entity.h"
#include "asset_helper.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class character : public entity, public observer
{

private:
	
	GLuint _bg;
	bool _added;
	
public:
	
	character();
	~character();
	
	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void draw();
	virtual void update(int msg_type, const observable_data &param);
	
};

#endif /* CHARACTER_H */