#include "GameWorldBase.h"
#include "iostream"
#include "Core/Texture.h"
#include "Core/Shader.h"
#include "Math.h"

#define pi 3.1415926

GameWorldBase::GameWorldBase(Engine* engine) :
	mEngine(engine)
{

}

GameWorldBase::~GameWorldBase()
{

}

bool GameWorldBase::Initialize(GLFWwindow* Window)
{

	//Get GLFW Window
	mWindow = Window;

	//Make Sure We Can Load Shaders
	if (!LoadShaders()) {
		cout << "ERROR::Failed to Load Shaders" << endl;
		return false;
	}

	//Create Sprite Data

	//Load Data

	return true;

}

void GameWorldBase::RunLoop(float deltaTime)
{
	ProcessInput();
	UpdateGameWorld(deltaTime);
	GenerateOutput();
}


void GameWorldBase::ShutDown()
{

}

void GameWorldBase::UpdateGameWorld(float deltaTime)
{

	//Update All Actors
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//Move UpPendingActors To mActors
	for (auto pending : mPendingActors) {
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}

	mPendingActors.clear();

	//Add Any Dead actors to a temp vector
	vector<Actor*> deadActors;

	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors) {
		delete actor;
	}
}



//Draw  Actor
void GameWorldBase::GenerateOutput()
{
	//Clear Last Output
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}


void GameWorldBase::AddActor(Actor* actor)
{
	//Add Actor To Vector
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}



void GameWorldBase::RemoveActor(Actor* actor)
{
	//Find And Erase it From mPendingActors and mActors

	// Is it in pending actors?
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

//Get the texture
Texture* GameWorldBase::GetTexture(string fileName)
{
	Texture* tex;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {

		//If have not been Create
		tex = new Texture();
		if (tex->Load(fileName)) {
			mTextures.emplace(fileName, tex);
		}
		else {
			//Error Read
			delete tex;
			tex = nullptr;
		}

	}
	return tex;
}

void GameWorldBase::LoadData()
{
	// Create Ball
	const int numBalls = 10;
	for (int i = 0; i < numBalls; i++)
	{
		//Create Balls
		//new Ball(this);
	}


}

void GameWorldBase::UnloadData()
{
	//Delete All Actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void GameWorldBase::ProcessInput()
{
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(mWindow);
	}
	mUpdatingActors = false;
}

bool GameWorldBase::LoadShaders()
{

	//Load Sprite Shader
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("./Shaders/Sprite.vert", "./Shaders/Sprite.frag")) {
		return false;
	}

	mSpriteShader->SetActive();

	//Set The View Projection , Same to All Actors
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
}



