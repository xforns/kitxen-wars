#ifndef OBSERVER_H
#define OBSERVER_H

#include "defs.h"

class observer 
{
	
public:
	
	virtual ~observer() {}
	virtual void update(const observable_data &param)=0;
	
};

#endif /* OBSERVER_H */