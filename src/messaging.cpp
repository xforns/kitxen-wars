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


void messaging::remove(observer *object)
{
	if(dynamic_cast<observer*>(object)==NULL)
	{
		return;
	}
	
	vector<observer*>::iterator it = _observers.begin();
	
	while(it!=_observers.end())
	{
		observer *obs = (*it);
		
		if(typeid(*object)==typeid((*obs)))
		{
			_observers.erase(it);
			break;
		}
		++it;
	}
	
}


void messaging::notify(int msg_type, const observable_data &t)
{
	vector<observer*>::iterator it;
	
	for(it=_observers.begin(); it!=_observers.end(); ++it)
	{
		if(*it==NULL)
		{
			continue;
		}
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

