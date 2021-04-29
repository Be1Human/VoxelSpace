#include "MoveComponent.h"
#include "Component.h"
#include "Core/Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder /*= 10*/):
Component(owner,updateOrder)
, mAngularSpeed(0.0f)
, mForwardSpeed(0.0f)

{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		// Screen wrapping (for asteroids)
		if (pos.x < -512.0f) { pos.x = 510.0f; }
		else if (pos.x > 512.0f) { pos.x = -510.0f; }
		if (pos.y < -384.0f) { pos.y = 382.0f; }
		else if (pos.y > 384.0f) { pos.y = -382.0f; }

		mOwner->SetPosition(pos);
	}

}
