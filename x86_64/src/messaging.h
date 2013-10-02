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
	
	static vector<observer*> _observers;
	static pthread_mutex_t _mutex;
	
	
	messaging();
	~messaging();
	
	static void *t_notify(void *vobject);
	
public:
	
	static messaging &getInstance()
	{
		static messaging instance;
		
		return instance;
	}
	
	void add(observer *object);
	void remove(observer *object);
	void notify(const observable_data &t);
		
};

#endif /* MESSAGING_H */