#pragma once
#include <vector>
#include "Actor.h"
#include <glad/glad.h>
#include "Ball.h"

using namespace std;

class GameWorld {

public:
	//Constructor And Destructor
	GameWorld(class Engine* engine);
	virtual ~GameWorld();


	//Initialize Game
	bool Initialize();

	//Run the Game Loop Until the Game is Over
	void RunLoop(float deltaTime);

	//ShutDown the Game
	void ShutDown();

	//UpdateGame
	void UpdateGameWorld(float deltaTime);


	//Add And Remove Actor
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);


	//Sprite(Visualize Actor)
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	/*
	*	"Custom Game Object Function"
	*	Write Your Specific Game Object Here
	*/
	void AddBall(class Ball* ast);
	void RemoveBall(class Ball* ast);
	vector<class Ball*>& GetAsteroids() { return mBalls; }


private:

	//Process Game Input
	void ProcessInput();

	//LoadShaders
	bool LoadShaders();

	//Generate Visual Graphics
	void GenerateOutput();

	void CreateSpriteVerts();


	//Load Data to Create Object
	void LoadData();
	void UnloadData();

	//Sprite Shader
	class Shader* mSpriteShader;
	// Sprite vertex array
	class VertexArray* mSpriteVerts;

	bool mUpdatingActors;

	// All the actors in the game
	vector<class Actor*> mActors;
	// Any pending actors
	vector<class Actor*> mPendingActors;

	//All Sprites
	vector<class SpriteComponent*> mSprites;

	//Engine Pointer
	class Engine* mEngine;

	//Custom Game Object
	vector<class Ball*> mBalls;

};