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
	void clear();
	void set_bounds(int x1, int y1, int x2, int y2);
	
	void add(entity_ptr ptr);
	void remove(entity_ptr ptr);
};

#endif /* COLLISION_SYSTEM_H */