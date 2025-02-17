#include "shapeFactory.h"
#include "shape.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
int ShapeFactory::counter = 0;
void ShapeFactory::init()
{
	counter++;
	srand((unsigned int)time(0) * counter);

	shapeArr[0].init(Shape::eshape::I, GameConfig::SHAPE_CH);
	shapeArr[1].init(Shape::eshape::L, GameConfig::SHAPE_CH);
	shapeArr[2].init(Shape::eshape::L_MIRRORED, GameConfig::SHAPE_CH);
	shapeArr[3].init(Shape::eshape::SQUARE, GameConfig::SHAPE_CH);
	shapeArr[4].init(Shape::eshape::Z, GameConfig::SHAPE_CH);
	shapeArr[5].init(Shape::eshape::Z_MIRRORED, GameConfig::SHAPE_CH);
	shapeArr[6].init(Shape::eshape::PLUS, GameConfig::SHAPE_CH);
}

Shape ShapeFactory::alloc() const
{
	int shapeIndex = (rand() % GameConfig::NUM_OF_SHAPE_KINDS);
	return shapeArr[shapeIndex];
}