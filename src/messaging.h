#ifndef MESSAGING_H
#define MESSAGING_H

#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>

#include "observer.h"
#include "defs.h"

using namespace std;


class messaging
{

private:
	
	messaging();
	~messaging();
	
	static vector<observer*> _observers;
	static pthread_mutex_t _mutex;
	
public:
	
	static messaging &getInstance()
	{
		static messaging instance;
		
		return instance;
	}
	
	void add(observer *object);
	static void *t_add(void *vobject);
	
	void remove(observer *object);
	static void *t_remove(void *vobject);
	
	void notify(const observable_data &t);
	static void *t_notify(void *vobject);
		
};

#endif /* MESSAGING_H */