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
	bool _dead;
	
public:
	
	entity();
	virtual ~entity();
	
	virtual void start()=0;
	virtual void stop()=0;
	virtual void update()=0;
	virtual void draw()=0;
	
	entity_type type();
	
	void x_y(double x, double y)
	{
		_pos.x = x;
		_pos.y = y;
	}
	
	void x(double x)
	{
		_pos.x = x;
	}
	
	void y(double y)
	{
		_pos.y = y;
	}
	
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
	
	double cx()
	{
		return _pos.x + _w/2;
	}
	
	double cy()
	{
		return _pos.y + _h/2;
	}
	
	bool is_dead()
	{
		return _dead;
	}
	
	void set_dead(bool is_dead)
	{
		_dead = is_dead;
	}
	
};

#endif /* ENTITY_H */