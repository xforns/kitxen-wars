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
	
	// Notifies all registered receivers with an object of type
	// observable_data.
	// The method is static as it's being used in a thread of its own.
	// Params:
	//  vobject:
	static void *t_notify(void *vobject);
	
public:
	
	// Obtains an instance of this class acting as a singleton.
	// Returns:
	//  messaging: This class' instance.
	static messaging &getInstance()
	{
		static messaging instance;
		
		return instance;
	}
	
	// Adds an observer to the messaging system.
	// Params:
	//  object: Class extending the observer class.
	void add(observer *object);
	
	// Removes an observer from the messaging system.
	// Params:
	//  object: Class extending the observer class.
	void remove(observer *object);
	
	// Entry point for senders that want to send a message to subscribed receivers.
	// This method creates a new thread and calls t_notify for the final notification.
	// Params:
	//  t: Object of type observable_data.
	void notify(const observable_data &t);
		
};

#endif /* MESSAGING_H */