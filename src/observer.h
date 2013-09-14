#ifndef OBSERVER_H
#define OBSERVER_H

#include "defs.h"

class observer 
{
	
public:
	
	virtual ~observer() {}
	virtual void update(int msg_type, const observable_data &param)=0;
	
};

#endif /* OBSERVER_H */