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

class collision_system
{
	
private:
	
	static int _bound_x1, _bound_x2, _bound_y1, _bound_y2;
	static vector <entity*> _entities;
	static bool _cancel_thread;
	static pthread_mutex_t _mutex;
	
	static void *t_add(void *vobject);
	static void *t_remove(void *vobject);
	static void *t_update(void *);
	static unsigned int is_collision(entity *obj, entity *obj2);
	
public:
	
	collision_system();
	~collision_system();
	
	void start();
	void stop();
	void clear();
	void set_bounds(int x1, int y1, int x2, int y2);
	
	void add(entity *object);
	void remove(entity *object);
};

#endif /* COLLISION_SYSTEM_H */