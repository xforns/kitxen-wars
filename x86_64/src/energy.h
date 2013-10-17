#ifndef ENERGY_H
#define ENERGY_H

#include <OpenGL/OpenGL.h>

#include "entity.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

class energy : public observer 
{

protected:
	
	pt _pos;
	double _w;
	double _h;
	
	GLuint _bg;
	
	int _en;
	
public:
	
	energy();
	~energy();
	
	void start();
	void stop();
	void update();
	void draw();
	
	virtual void update(const observable_data &param);
	
};

#endif /* ENERGY_H */