#pragma once
#include<vector>
#include<unordered_map>
#include "Core/Actor.h"
#include <GLFW/glfw3.h>

using namespace std;

class GameWorldBase 
{
	
public:
	//Constructor And Destructor
	GameWorldBase(class Engine* engine);
	virtual ~GameWorldBase();


	//Initialize Game
	virtual bool Initialize(GLFWwindow* mWindow);

	//Run the Game Loop Until the Game is Over
	virtual void RunLoop(float deltaTime);

	//ShutDown the Game
	virtual void ShutDown();

	//UpdateGame
	virtual void UpdateGameWorld(float deltaTime);


	//Add And Remove Actor
	virtual void AddActor(class Actor* actor);
	virtual void RemoveActor(class Actor* actor);

	//Get Texture
	class Texture* GetTexture(string fileName);

	//Process Game Input
	virtual void ProcessInput();

	//LoadShaders
	virtual bool LoadShaders();


	//Generate Visual Graphics 
	virtual void GenerateOutput();


	//Sprite Shader
	class Shader* mSpriteShader;
	


	/*
	*	"Custom Game Object Function"
	*	Write Your Specific Game Object Here
	*/

private:
	


	// All the actors in the game
	vector<class Actor*> mActors;

	// Any pending actors
	vector<class Actor*> mPendingActors;

	//Texture
	unordered_map<string, class Texture*> mTextures;

	//Engine Pointer
	class Engine* mEngine;

	//GLFW Window Context
	GLFWwindow* mWindow;


	bool mUpdatingActors;
		

};