#pragma once
#include "AGameObject.h"
//represents an empty game object. use this to attach components that need to utilize the update() function, but not need to render
//a sprite_main
class EmptyGameObject : public AGameObject
{
public:
	EmptyGameObject(string name, int level);
	~EmptyGameObject();
	void initialize();
};