#include "Actor.h"
#include "GameWorld.h"
#include "Component.h"

Actor::Actor(GameWorld* gameWorld) :
	mState(EActive), mPosition(Vector2::Zero), mScale(1.0f), mRotation(0.0f), mGameWorld(gameWorld), mRecomputeWorldTransform(true)
{
	//When Construct,Add Actor To GameWorld
	mGameWorld->AddActor(this);
}


Actor::~Actor()
{
	//Remove Actor Form GameWorld
	mGameWorld->RemoveActor(this);
}


void Actor::Update(float deltaTime)
{
	if (mState == EActive) {

		//Compute TrasForm
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		//Compute TrasForm
		ComputeWorldTransform();
	}
}


void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}


void Actor::UpdateActor(float deltaTime)
{

}

void Actor::ActorInput(const uint8_t* keyState)
{

}

//Compute TrasForm
void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform) {
		mRecomputeWorldTransform = false;

		//Scale,then rotate, then translate
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

		//Inform Components world transform updated
		for (auto comp : mComponents) {
			comp->GetUpdateOrder();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	//Find the Component Order And Insert it in It(The Bigger The Higher)
	int myOrder = component->GetUpdateOrder();

	auto iter = mComponents.begin();

	for (; iter != mComponents.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}

	}
	//Insert the Component
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	//Get The component Iterator
	auto iter = find(mComponents.begin(), mComponents.end(), component);
	//Erase It
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}

