#include "messaging.h"

bool messaging::_notifyInProgress;
vector <observer*>messaging::_observers;

/****************************************************************

							public

****************************************************************/


void messaging::add(observer *object)
{
	while(_notifyInProgress);
	
	_notifyInProgress = true;
	
	if(dynamic_cast<observer*>(object)==NULL)
	{
		//std::cout << std::endl << "  - Could not add object to observers" << std::endl << std::flush;
		return;
	}
	
	_observers.push_back( object );
	
	_notifyInProgress = false;
}


void messaging::remove(observer *object)
{
	while(_notifyInProgress);
	
	_notifyInProgress = true;
	
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
	
	_notifyInProgress = false;
}


void messaging::notify(const observable_data &t)
{
	pthread_t thread;
	
	observable_data *nonconst = new observable_data();
	nonconst->msg_type = t.msg_type;
	nonconst->a = t.a;
	nonconst->b = t.b;
	nonconst->c = t.c;
	nonconst->d = t.d;
	
	pthread_create(&thread,NULL,&t_notify,nonconst);
}


void *messaging::t_notify(void *vobject)
{
	while(_notifyInProgress);
	
	observable_data* t = (observable_data *)vobject;
	
	_notifyInProgress = true;
	
	vector<observer*>::iterator it;
	
	for(it=_observers.begin(); it!=_observers.end(); ++it)
	{
		if(*it==NULL)
		{
			continue;
		}
		
		observer *obs = *it;
		
		if(dynamic_cast<observer*>(obs)==NULL)
		{
			continue;
		}
		
		(*it)->update(*t);
	}
	
	_notifyInProgress = false;
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

