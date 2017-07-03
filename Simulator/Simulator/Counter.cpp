#include "Counter.h"

Counter::Counter(){
	// c belongs to a set {0,1,2,3}
	// 0: strongly taken
	// 1: weakly taken
	// 2: weakly untaken
	// 3: strongly untaken
	c[0] = 1;
	c[1] = 1;
}

Counter & Counter::operator++()
{
	if (c[0]) {
		c[1] = 1;
 	}else {
		if (!c[1]) c[1] = 1;
		else {
			c[0] = 1;
			c[1] = 0;
		}
	}
	return *this;
}

Counter & Counter::operator--()
{
	if (c[1]) {
		c[1] = 0;
	}else {
		if (c[0]) {
			c[0] = 0;
			c[1] = 1;
		}
	}
	return *this;
}

bool Counter::istaken()
{
	if (c[0])return true;
	else return false;
}
