#include "messaging.h"


/****************************************************************

							public

****************************************************************/


void messaging::add(observer *object)
{
	
	if(dynamic_cast<observer*>(object)==NULL)
	{
		return;
	}
	
	_observers.push_back( object );
}


void messaging::notify(int msg_type, const observable_data &t)
{
	vector<observer*>::iterator it;
	
	for(it=_observers.begin(); it!=_observers.end(); ++it)
	{
		(*it)->update(msg_type,t);
	}
}


/****************************************************************

							private

****************************************************************/


messaging::messaging()
{
}


messaging::~messaging()
{
}

