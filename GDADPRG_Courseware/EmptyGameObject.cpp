#include "EmptyGameObject.h"

EmptyGameObject::EmptyGameObject(string name, int level) : AGameObject(name, level)
{

}

EmptyGameObject::~EmptyGameObject()
{
	AGameObject::~AGameObject();
}

void EmptyGameObject::initialize()
{
}