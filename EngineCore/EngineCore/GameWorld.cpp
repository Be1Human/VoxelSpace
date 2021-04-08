#include "GameWorld.h"
#include <vector>
#include "VertexArray.h"
#include "Shader.h"
#include "iostream"
#include "SpriteComponent.h"
#include "Ball.h"

GameWorld::GameWorld(Engine* engine):
	mSpriteShader(nullptr), mSpriteVerts(nullptr), mEngine(engine)
{


}

GameWorld::~GameWorld()
{

}

bool GameWorld::Initialize()
{

	//Make Sure We Can Load Shaders
	if (!LoadShaders()) {
		cout << "ERROR::Failed to Load Shaders" << endl;
		return false;
	}

	//Create Sprite Data
	CreateSpriteVerts();

	//Load Data
	LoadData();

	return true;

}

void GameWorld::RunLoop(float deltaTime)
{
	ProcessInput();
	UpdateGameWorld(deltaTime);
	GenerateOutput();
}


void GameWorld::ShutDown()
{
	delete mSpriteVerts;

	mSpriteShader->Unload();
	delete mSpriteShader;

	UnloadData();
}

void GameWorld::UpdateGameWorld(float deltaTime)
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


void GameWorld::GenerateOutput()
{
	//Clear Last Output
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Set shader/vao as active
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();


	// Draw Actors
	//cout << "TEST::The Size of mSprites:" << mSprites.size() << endl;
	for (auto sprite : mSprites) {
		//cout << 1 << endl;
		sprite->Draw(mSpriteShader);
	}

	//TEST:Draw Objects
	// Scale the quad by the width/height of texture
	//glDrawElements(
	//	GL_TRIANGLES,
	//	6,
	//	GL_UNSIGNED_INT,
	//	nullptr
	//);

}


void GameWorld::AddActor(Actor* actor)
{
	//Add Actor To Vector
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}



void GameWorld::RemoveActor(Actor* actor)
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



void GameWorld::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}
	mSprites.insert(iter,sprite);
}




void GameWorld::RemoveSprite(SpriteComponent* sprite)
{
	//Find the Sprite
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);

}



//Only For Test
void GameWorld::CreateSpriteVerts()
{
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
	//cout << sizeof(mSpriteVerts) << endl;
}



void GameWorld::LoadData()
{
	// Create Ball
	const int numBalls = 20;
	for (int i = 0; i < numBalls; i++)
	{
		new Ball(this);
	}

}

void GameWorld::UnloadData()
{
	//Delete All Actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void GameWorld::ProcessInput()
{

}

bool GameWorld::LoadShaders()
{

	//Load Sprite Shader
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("./Transform.vert", "./Basic.frag")) {
		return false;
	}
	
	mSpriteShader->SetActive();

	//Set The View Projection , Same to All Actors
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	return true;
}

void GameWorld::AddBall(Ball* ast)
{
	mBalls.emplace_back(ast);
}


void GameWorld::RemoveBall(Ball* ast)
{
	auto iter = find(mBalls.begin(), mBalls.end(), ast);
	if (iter != mBalls.end())
	{
		mBalls.erase(iter);
	}
}

