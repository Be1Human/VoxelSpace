#include "Component.h"
#include "Actor.h"

Component::Component(class Actor* owner, int updateOrder /*= 100*/)
	:mOwner(owner), mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{

}

void Component::ProcessInput(const uint8_t* keyState)
{

}

