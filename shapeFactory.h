#ifndef __SHAPEFACTORY_H
#define __SHAPEFACTORY_H
#include "shape.h"

class ShapeFactory
{
private:
	static int counter;
	Shape shapeArr[GameConfig::NUM_OF_SHAPE_KINDS];
public:
	void init();
	Shape alloc() const;
};


#endif 

