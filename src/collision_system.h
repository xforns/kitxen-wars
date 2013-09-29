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
	
	/****************************************************************
	
								private
	
	****************************************************************/
	
private:
	
	static int _bound_x1, _bound_x2, _bound_y1, _bound_y2;
	
	static vector <entity*> _entities;
	
	static bool _cancel_thread;
	
	/****************************************************************
	
								public
	
	****************************************************************/
	
public:
	
	
	collision_system() {
		
	}
	
	
	~collision_system()
	{
		_entities.clear();
	}
	
	
	void start()
	{
		_cancel_thread = false;
		
		pthread_t thread;
		
		pthread_create(&thread,NULL,&t_update,NULL);
	}
	
	
	void stop()
	{
		_cancel_thread = true;
	}
	
	
	void clear()
	{
		
	}
	
	
	void set_bounds(int x1, int y1, int x2, int y2)
	{
		_bound_x1 = x1;
		_bound_x2 = x2;
		_bound_y1 = y1;
		_bound_y2 = y2;
	}
	
	
	void add(entity *object)
	{
		if(dynamic_cast<entity*>(object)==NULL)
		{
			return;
		}
		
		_entities.push_back(object);
	}
	
	
	void remove(entity *object)
	{
		if(dynamic_cast<entity*>(object)==NULL)
		{
			return;
		}
		
		vector<entity*>::iterator it = find(_entities.begin(),_entities.end(),object);
		if(it==_entities.end())
		{
			return;
		}
		_entities.erase(it);
	}
	
	
	
	static unsigned int is_collision(entity *obj, entity *obj2)
	{
		vector <vec2>all_axis;
		all_axis.push_back( vec2(1,0).unit() );
		all_axis.push_back( vec2(0,1).unit() );
		
		// check for both axis
		
		vector <vec2>::iterator all_it;
		for(all_it=all_axis.begin();all_it!=all_axis.end();++all_it)
		{
			vec2 axis = *all_it;
			
			bool axis_x = axis.x()==1;
			
			// project all sides
		
			vector <vec2>proj1;
			proj1.push_back( vec2( obj->x() , obj->y() ) * axis );
			proj1.push_back( vec2( obj->x() , obj->yh() ) * axis );
			proj1.push_back( vec2( obj->xw() , obj->y() ) * axis );
			proj1.push_back( vec2( obj->xw() , obj->yh() ) * axis );
		
			vector <vec2>proj2;
			proj2.push_back( vec2( obj2->x() , obj2->y() ) * axis );
			proj2.push_back( vec2( obj2->x() , obj2->yh() ) * axis );
			proj2.push_back( vec2( obj2->xw() , obj2->y() ) * axis );
			proj2.push_back( vec2( obj2->xw() , obj2->yh() ) * axis );
		
			// get max and min for each projected object
		
			double obj1_min = numeric_limits<float>::max(), obj1_max = -obj1_min;
			vector <vec2>::iterator it;
			for(it=proj1.begin();it!=proj1.end();++it)
			{
				vec2 vobj = *it;
				
				double val = axis_x ? vobj.x() : vobj.y();
				obj1_min = val < obj1_min ? val : obj1_min;
				obj1_max = val > obj1_max ? val : obj1_max;
			}
		
			double obj2_min = numeric_limits<float>::max(), obj2_max = -obj1_min;
			for(it=proj2.begin();it!=proj2.end();++it)
			{
				vec2 vobj = *it;
			
				double val = axis_x ? vobj.x() : vobj.y();
				obj2_min = val < obj2_min ? val : obj2_min;
				obj2_max = val > obj2_max ? val : obj2_max;
				
			}
		
			// check whether these segments collide
		
			if( ( obj2_min >= obj1_min ) && ( obj2_min <= obj1_max ) )
			{
				return axis_x ? COLLISION_LEFT : COLLISION_BOTTOM;
			}
			else if( ( obj1_min >= obj2_min ) && ( obj1_min <= obj2_max ) )
			{
				return axis_x ? COLLISION_RIGHT : COLLISION_TOP;
			}
			
		}
		
		return COLLISION_NONE;
	}
	
	
	static void *t_update(void *)
	{
		vector<entity*>::iterator it;
		
		for(it=_entities.begin();it!=_entities.end();++it)
		{
			entity *object = *it;
			
			// bounds check
			
			if( object->x() <= _bound_x1 )
			{
				
			}
			else if( object->x() >= _bound_x2 )
			{
				
			}
			else if( object->y() <= _bound_y1 )
			{
				
			}
			else if( object->y() >= _bound_y2 )
			{
				
			}
			
			// enemies, fire against enemies, fire against character and bomb collisions
			
			vector<entity*>::iterator it2;
			for(it2=_entities.begin();it2!=_entities.end();++it2)
			{
				entity *object2 = *it;
				
				unsigned int collision = is_collision(object,object2);
				// if collision, notify possible receptors
				if(collision!=COLLISION_NONE)
				{
					observable_data data;
					data.msg_type = MSG_COLLISION;
					data.a = object->type();
					data.b = object->type();
					data.c = collision;
					messaging::getInstance().notify(data);
				}
			}
		}
		
		if(_cancel_thread)
		{
			pthread_exit(NULL);
		}
	}
	
};

#endif /* COLLISION_SYSTEM_H */