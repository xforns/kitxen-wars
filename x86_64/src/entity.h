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
	
	// Next methods are virtual and therefore mandatory for derived classes to implement.
	
	// Convenience method for doing preparation stuff.
	virtual void start()=0;
	
	// Convenience method in case we want to 'halt' the state of the object.
	virtual void stop()=0;
	
	// The update method should ideally deal with the internal state of the object.
	virtual void update()=0;
	
	// The draw should do what its name says.
	virtual void draw()=0;
	
	// Returns the type of the derived entity. Normally this type is defined in 
	// the derived classes constructors.
	// Returns:
	//  entity_type: A type of the enumeration entity_type.
	entity_type type();
	
	// Next functions are convenience getters and setters dealing with the position and size
	// of the entities.
	
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
	
	// All entities can be in a 'dead' state, which normally means 
	// the object is susceptible for removal.
	// Returns:
	//  bool: Whether the object is 'dead'.
	bool is_dead()
	{
		return _dead;
	}
	
	// Sets (or unsets) the object in the 'dead' state.
	// Params:
	//  is_dead: If true, the object is set in the 'dead' state.
	void set_dead(bool is_dead)
	{
		_dead = is_dead;
	}
	
};

#endif /* ENTITY_H */