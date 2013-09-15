#ifndef MESSAGING_H
#define MESSAGING_H

#include <map>
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
	
	vector<observer*> _observers;
	
public:
	
	static messaging &getInstance()
	{
		static messaging instance;
		
		return instance;
	}
	
	void add(observer *object);
	void remove(observer *object);
	
	void notify(int msg_type, const observable_data &t);
		
};

#endif /* MESSAGING_H */