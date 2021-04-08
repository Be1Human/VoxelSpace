#include "Ball.h"
#include "Random.h"
#include "GameWorld.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Ball::Ball(GameWorld* gameWorld):
	Actor(gameWorld)
{
	// Initialize to random position/orientation
	Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f),Vector2(512.0f, 384.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);

	// Create a move Component
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);
	mc->SetAngularSpeed(2.f);

	// Add to mAsteroids in game
	gameWorld->AddBall(this);
}

Ball::~Ball()
{
	GetGameWorld()->RemoveBall(this);
}
