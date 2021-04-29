#include "InputComponent.h"

InputComponent::InputComponent(class Actor* owner):
	MoveComponent(owner),
	mForwardKey(0),
	mBackKey(0)
{
	
}


void InputComponent::ProcessInput(GLFWwindow* mWindow)
{
	//Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	if (glfwGetKey(mWindow, mForwardKey) == GLFW_PRESS) {
		forwardSpeed += mMaxForwardSpeed;
	}
	if (glfwGetKey(mWindow, mBackKey) == GLFW_PRESS) {
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	//Calculate Angular speed for MoveComponent
	//float angularSpeed = 0.0f;
	//if (glfwGetKey(mWindow, mClockwiseKey) == GLFW_PRESS) {
	//	angularSpeed += mMaxAngularSpeed;
	//}
	//if (glfwGetKey(mWindow, mCounterClockwiseKey) == GLFW_PRESS) {
	//	angularSpeed -= mMaxAngularSpeed;
	//}
	//SetAngularSpeed(angularSpeed);

}
