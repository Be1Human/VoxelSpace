#pragma once
#include <vector>
#include "Math/Math.h"
#include <GLFW/glfw3.h>

using namespace std;

class Actor
{
public:
	//Used To Track State Of Actor
	enum State {
		EActive,
		EPaused,
		EDead
	};

	//Constructor And Destructor
	Actor(class GameWorld* gameWorld);
	virtual ~Actor();

	//Update Actor(Update Actor and Component)
	void Update(float deltaTime);

	//Update All the Components Attached To the Actor
	void UpdateComponents(float deltaTime);

	//Derived Actor Update Code
	virtual void UpdateActor(float deltaTime);

	//Process Actor Input(InClude its Component Input)
	void ProcessInput(GLFWwindow* mWindow);

	//Derived Actor Input Update Code
	virtual void ActorInput(GLFWwindow* mWindow);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }


	//TransForm
	void ComputeWorldTransform(); //Compute World TransForm Matrix
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	//Get Actor Forward
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

	//Add And Remove Components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	//Get NowState
	State GetState() const { return mState; }


	//Get GameWorld
	class GameWorld* GetGameWorld() { return mGameWorld; }

private:
	//Actor's State
	State mState;

	//Transform
	Matrix4 mWorldTransform; //Can be Used to 2D and 3D
	Vector2 mPosition;
	float mScale;
	float mRotation;
	bool mRecomputeWorldTransform;

	//Store Actor Components
	vector<class Component*> mComponents;

	//Make A GameWorld Pointer
	class GameWorld* mGameWorld;

};
