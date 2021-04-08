#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	//Set Rotation
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	//Move ForWard
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
	float mAngularSpeed;
	float mForwardSpeed;

};
