#ifndef OBSERVER_H
#define OBSERVER_H

#include "defs.h"

class observer 
{
	
public:
	
	// Destructor as virtual, needed if we want derived classes to implement
	// the update function.
	virtual ~observer() {}
	
	// Main entry point for classes that want to receive messages from the
	// messaging system.
	// Params:
	//  param: Object of type observable_data.
	virtual void update(const observable_data &param)=0;
	
};

#endif /* OBSERVER_H */