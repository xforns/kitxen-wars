#include "messaging.h"

pthread_mutex_t messaging::_mutex;
vector <observer*>messaging::_observers;

/****************************************************************

							public

****************************************************************/


void messaging::add(observer *object)
{
	pthread_mutex_lock(&_mutex);
	
	_observers.push_back( object );
	
	pthread_mutex_unlock(&_mutex);
}


void messaging::remove(observer *object)
{
	pthread_mutex_lock(&_mutex);
	
	auto it = _observers.begin();
	
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
	
	pthread_mutex_unlock(&_mutex);
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
	nonconst->o1 = t.o1;
	nonconst->o2 = t.o2;
	
	pthread_create(&thread,NULL,&t_notify,nonconst);
}


void *messaging::t_notify(void *vobject)
{
	pthread_mutex_lock(&_mutex);
	
	observable_data *t = (observable_data *)vobject;
	
	for(auto it=_observers.begin(); it!=_observers.end(); ++it)
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
	
	pthread_mutex_unlock(&_mutex);
	
	pthread_exit(NULL);
}

/****************************************************************

							private

****************************************************************/


messaging::messaging()
{
	pthread_mutex_init(&_mutex, NULL);
}


messaging::~messaging()
{
	pthread_mutex_destroy(&_mutex);
}

