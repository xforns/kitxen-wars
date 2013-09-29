#ifndef ENTITY_H
#define ENTITY_H

#include "defs.h"

class entity
{

protected:
	
	pt _pos;
	double _w;
	double _h;
	entity_type _type;
	
public:
	
	entity();
	virtual ~entity();
	
	virtual void start()=0;
	virtual void stop()=0;
	virtual void update()=0;
	virtual void draw()=0;
	
	entity_type type();
	
	double x()
	{
		return _pos.x;
	}
	
	double y()
	{
		return _pos.y;
	}
	
	double xw()
	{
		return _pos.x + _w;
	}
	
	double yh()
	{
		return _pos.y + _h;
	}
	
};

#endif /* ENTITY_H */