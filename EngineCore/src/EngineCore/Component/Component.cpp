#include "Component.h"
#include "Core/Actor.h"

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

void Component::ProcessInput(GLFWwindow* mWindow)
{

}

