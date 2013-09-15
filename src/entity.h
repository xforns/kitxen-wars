#ifndef ENTITY_H
#define ENTITY_H

#include "defs.h"

class entity
{

protected:
	
	pt _pos;
	
public:
	
	entity();
	~entity();
	
	virtual void start()=0;
	virtual void stop()=0;
	virtual void update()=0;
	virtual void draw()=0;
	
};

#endif /* ENTITY_H */