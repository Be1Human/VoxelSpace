#pragma once
#include "Core/Actor.h"

class Littleboy : public Actor {
public:
	Littleboy(class GameWorld* gameWorld);

	//Update Actor(Update Actor and Component)
	void UpdateCharacter(float deltaTime);

	//
private:
};
