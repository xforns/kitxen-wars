#include "collision_system.h"

int collision_system::_bound_x1, collision_system::_bound_x2, collision_system::_bound_y1, collision_system::_bound_y2;
vector <entity_ptr> collision_system::_entities;
bool collision_system::_cancel_thread;
pthread_mutex_t collision_system::_mutex;


collision_system::collision_system() {}


collision_system::~collision_system()
{
	_entities.clear();
}


void collision_system::start()
{
	_cancel_thread = false;
	
	pthread_mutex_init(&_mutex, NULL);
	
	pthread_create(&_thread_update,NULL,&t_update,NULL);
}


void collision_system::stop()
{
	_cancel_thread = true;
	
	pthread_join(_thread_update,NULL);
	
	pthread_mutex_destroy(&_mutex);
}


void collision_system::clear()
{
	
}


void collision_system::set_bounds(int x1, int y1, int x2, int y2)
{
	_bound_x1 = x1;
	_bound_x2 = x2;
	_bound_y1 = y1;
	_bound_y2 = y2;
}


void collision_system::add(entity_ptr ptr)
{
	pthread_mutex_lock(&_mutex);
	
	_entities.push_back(ptr);
	
	pthread_mutex_unlock(&_mutex);
}


void collision_system::remove(entity_ptr ptr)
{
	pthread_mutex_lock(&_mutex);
	
	_entities.erase(remove_if(_entities.begin(),_entities.end(),ptr_contains(ptr.get())));
	
	pthread_mutex_unlock(&_mutex);
}


void *collision_system::t_update(void *)
{
	while(true)
	{
		pthread_mutex_lock(&_mutex);
		
		int pos_obj1 = 0;
		int pos_obj2 = 0;
		
		for(auto it=_entities.begin();it!=_entities.end();++it,pos_obj1++)
		{
			entity *object = (*it).get();
			
			// bounds check
			unsigned int collision = COLLISION_NONE;
			if( object->x() <= _bound_x1 )
			{
				collision = COLLISION_LEFT;
			}
			else if( object->xw() >= _bound_x2 )
			{
				collision = COLLISION_RIGHT;
			}
			else if( object->yh() >= _bound_y2 )
			{
				collision = COLLISION_TOP;
			}
			else if( object->y() <= _bound_y1 )
			{
				collision = COLLISION_BOTTOM;
			}
			
			if(collision!=COLLISION_NONE)
			{
				observable_data data;
				data.msg_type = MSG_COLLISION;
				data.a = object->type();
				data.b = TYPE_NONE;
				data.c = collision;
				data.o1 = *it;
				messaging::getInstance().notify(data);
			}
		
			// enemies, fire against enemies, fire against character and bomb collisions
		
			for(auto it2=_entities.begin();it2!=_entities.end();++it2,pos_obj2++)
			{
				entity_ptr ptr2 = *it2;
				if((*it).get()==ptr2.get())
				{
					continue;
				}
				entity *object2 = ptr2.get();
				
				unsigned int collision = is_collision(object,object2);
				
				// if collision, notify possible receptors
				if(collision!=COLLISION_NONE)
				{
					observable_data data;
					data.msg_type = MSG_COLLISION;
					data.a = object->type();
					data.b = object2->type();
					data.c = collision;
					data.o1 = *it;
					data.o2 = ptr2;
					messaging::getInstance().notify(data);
				}
			}
		}
		
		pthread_mutex_unlock(&_mutex);
		
		if(_cancel_thread)
		{
			finalize();
			pthread_exit(NULL);
		}
	}
}


unsigned int collision_system::is_collision(entity *obj, entity *obj2)
{
	vector <vec2>all_axis;
	all_axis.push_back( vec2(1,0).unit() );
	all_axis.push_back( vec2(0,1).unit() );
	
	// check for both axis
	
	bool collision = true;
	double diff_axis_x = 0.f, diff_axis_y = 0.f;
	unsigned int horizontal_collision, vertical_collision;
	
	for(auto all_it=all_axis.begin();all_it!=all_axis.end();++all_it)
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
		for(auto it=proj1.begin();it!=proj1.end();++it)
		{
			vec2 vobj = *it;
			
			double val = axis_x ? vobj.x() : vobj.y();
			obj1_min = val < obj1_min ? val : obj1_min;
			obj1_max = val > obj1_max ? val : obj1_max;
		}
	
		double obj2_min = numeric_limits<float>::max(), obj2_max = -obj1_min;
		for(auto it=proj2.begin();it!=proj2.end();++it)
		{
			vec2 vobj = *it;
		
			double val = axis_x ? vobj.x() : vobj.y();
			obj2_min = val < obj2_min ? val : obj2_min;
			obj2_max = val > obj2_max ? val : obj2_max;
			
		}
		
		// check whether these segments collide
		
		if( ( obj1_max >= obj2_min ) && ( obj1_max <= obj2_max ) ) 
		{
			collision &= true;
			
			if(axis_x)
			{
				diff_axis_x = obj2_max - obj1_min;
				horizontal_collision = COLLISION_RIGHT;
			}
			else
			{
				diff_axis_y = obj2_max - obj1_min;
				vertical_collision = COLLISION_BOTTOM;
			}
		}
		else if( ( obj2_max >= obj1_min ) && ( obj2_max <= obj1_max ) )
		{
			collision &= true;
			
			if(axis_x)
			{
				diff_axis_x = obj1_max - obj2_min;
				horizontal_collision = COLLISION_LEFT;
			}
			else
			{
				diff_axis_y = obj1_max - obj2_min;
				vertical_collision = COLLISION_TOP;
			}
		}
		else
		{
			collision &= false;
		}
		
	}
	
	if(collision)
	{
		return diff_axis_x >= diff_axis_y ? horizontal_collision : vertical_collision;
						
	}
	
	return COLLISION_NONE;
}


void collision_system::finalize()
{
	_entities.clear();
}


