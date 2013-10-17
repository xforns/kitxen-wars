#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <iostream>

#include "SOIL.h"
#include "entity.h"
#include "defs.h"
#include "messaging.h"
#include "vec2.h"

using namespace std;

typedef shared_ptr<entity> entity_ptr;

class collision_system
{
	
private:
	
	static int _bound_x1, _bound_x2, _bound_y1, _bound_y2;
	static vector <entity_ptr> _entities;
	static bool _cancel_thread;
	static pthread_mutex_t _mutex;
	pthread_t _thread_update;
	
	static void *t_update(void *);
	static unsigned int is_collision(entity *obj, entity *obj2);
	static void finalize();
	
public:
	
	collision_system();
	~collision_system();
	
	void start();
	void stop();
	
	// Sets the game boundaries (which anyway correspond to the active window).
	// Params:
	//  x1:
	//  y1:
	//  x2:
	//  y2:
	void set_bounds(int x1, int y1, int x2, int y2);
	
	// Add an object of base type Entity to the collision system,
	// so it's taken in account in all the processing.
	// Params:
	//  ptr: Shared pointer of type Entity.
	void add(entity_ptr ptr);
	
	// Removes an object of base type Entity from the collision system.
	// Params:
	//  ptr: Shared pointer of type Entity.
	void remove(entity_ptr ptr);
	
};

#endif /* COLLISION_SYSTEM_H */