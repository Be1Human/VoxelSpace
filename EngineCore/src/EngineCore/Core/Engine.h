#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "Game_Project/GameWorld.h"


using namespace std;

class Engine {
public:
	Engine();

	//Initialize Engine
	bool Initialize();
	
	//Run the Engine Loop Until the Game is Over
	void RunLoop();

	//ShutDown the Engine
	void ShutDown();

private:
	void ProcessInput();

	//Update Engine Every Tick
	void UpdateEngine();

	//Generate Visual Graphics
	void GenerateOutput();

	bool InitlizeGame();

	//Base Parameter
	GLFWwindow* mWindow;

	double mTicksCount;

	bool mIsRunning;

	bool mIsClampFPS;

	//Control Game
	bool mIsStartGameWorld;
	bool mIsInitGameWorld;
	bool mIsGameInit;

	//GameWorld Pointer
	class GameWorld* mGameWorld;

};
