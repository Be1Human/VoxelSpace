#pragma once
#include <cstdint>
#include <GLFW/glfw3.h>

class Component
{
public:
	//Constructor And Destructor
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	//Update this Component by Delta Time
	virtual void Update(float deltaTime);
	//Process Input
	virtual void ProcessInput(GLFWwindow* mWindow);
	//Call When world transform Change
	virtual void OnUpdateWorldTransform() {};

	//Get Update Order Function
	int GetUpdateOrder() const { return mUpdateOrder; };

protected:
	
	//Owning Actor
	class Actor* mOwner;

	// Update order of Component
	int mUpdateOrder;


};

