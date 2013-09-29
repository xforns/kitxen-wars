#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class vec2
{
	/****************************************************************
	
								private
	
	****************************************************************/
	
private:
	
	double _x;
	double _y;
	double _m;
	double _a;
	
	/****************************************************************
	
								public
	
	****************************************************************/
	
public:

	vec2() {}
	
	vec2(double x, double y) : _x(x),_y(y)
	{
		_m = sqrt( _x * _x + _y * _y );
		_a = atan2(_y,_x);
	}
	
	~vec2() {}
	
	double x()
	{
		return _x;
	}
	
	double y()
	{
		return _y;
	}
	
	void x(double x)
	{
		_x = x;
		_m = sqrt( _x * _x + _y * _y );
		_a = atan2(_y,_x);
	}
	
	void y(double y)
	{
		_y = y;
		_m = sqrt( _x * _x + _y * _y );
		_a = atan2(_y,_x);
	}
	
	vec2 unit()
	{
		vec2 foo;
		foo.x( _x / _m );
		foo.y( _y / _m );
		
		return foo;
	}
	
	vec2 operator+(vec2 &other) const
	{
		vec2 foo;
		foo.x( this->_x + other.x() );
		foo.y( this->_y + other.y() );
		
		return foo;
	}
	
	vec2 operator-(vec2 &other) const
	{
		vec2 foo;
		foo.x( _x - other.x() );
		foo.y( _y - other.y() );
		
		return foo;
	}
	
	vec2 operator*(vec2 &other) const
	{
		vec2 foo;
		foo.x( _x * other.x() );
		foo.y( _y * other.y() );
		
		return foo;
	}
	
};

#endif /* VEC2_H */