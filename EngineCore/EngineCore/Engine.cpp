#include "Engine.h"
#include "Shader.h"
#include "VertexArray.h"
#include "GameWorld.h"

//Construct Function
Engine::Engine()
:mWindow(nullptr), mIsRunning(true),  mTicksCount(0),mIsClampFPS(false),
mIsStartGameWorld(false), mGameWorld(nullptr), mIsInitGameWorld(false)
{

}


//Window Size Change CallBack Function
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//Init the Engine
bool Engine::Initialize()
{


	//Init GLFW Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set A Window Parameter
	mWindow = glfwCreateWindow(800, 600, "VoxelSpace", nullptr, nullptr);


	//Check Window
	if (mWindow == nullptr) {
		cout << "ERROR::Failed to create GLFW window" << endl;
		glfwTerminate();
		return false;
	}

	//Set WindwoContext As Now Procedure Context
	glfwMakeContextCurrent(mWindow);


	//Init Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "ERROR::Failed to initialize GLAD" << endl;
		return false;
	}

	//Set View Size
	glViewport(0, 0, 800, 600);

	//Follow the Window Size Change
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	//Get the Init Time(Set to ms)
	mTicksCount = glfwGetTime();

	return true;
}


void Engine::RunLoop()
{

	//Loop the Engine Until It should be Closed
	while (!glfwWindowShouldClose(mWindow)) {
		//Process All Input
		ProcessInput();
		//Update Data
		UpdateEngine();
		//Draw Graphics
		GenerateOutput();
	}

}

void Engine::ShutDown()
{

	//Release GLFW
	glfwTerminate();

}

void Engine::ProcessInput()
{

	//Get the KeyBoard Press
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		mIsRunning = false;
		cout << "VS:successfully turn off" << endl;
		glfwSetWindowShouldClose(mWindow, !mIsRunning);
	}

	//Start Game
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS) {
		mIsStartGameWorld = true;
		cout << "TEST:Successfully Press Start game Key" << endl;
	}

}


void Engine::UpdateEngine()
{
	//Clamp FPS
	if (mIsClampFPS) {

	}

	//Get DeltaTime
	double deltaTime = (glfwGetTime() - mTicksCount);

	//Clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	//Save Now Time for next DeltaTime Calculate
	mTicksCount = glfwGetTime();


	//TODO:

	//Start or End Game
	if (mIsStartGameWorld) {
		if (!mIsInitGameWorld) {
			mIsInitGameWorld = true;
			mGameWorld = new GameWorld(this);
			if (!mGameWorld->Initialize()) {
				cout << "ERROR::Fail to Initialize Game" << endl;
			}
		}

		//Update GameWorld
		if (mGameWorld) {
			//cout << "TEST::Game Running!"<<endl;
			mGameWorld->RunLoop(deltaTime);
		}
	}
	else {
		if (mGameWorld) {
			mGameWorld->ShutDown();
			delete mGameWorld;
		}
		mIsInitGameWorld = false;

	}

}


void Engine::GenerateOutput()
{

	//Swap ARGB Buffer
	glfwSwapBuffers(mWindow);

	//Detect Event(Such as KeyBoard¡¢Mouse)
	glfwPollEvents();
}


