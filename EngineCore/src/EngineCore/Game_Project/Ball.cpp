#include "Ball.h"
#include "Math/Random.h"
#include "GameWorld.h"
#include "Core/Actor.h"
#include "Component/SpriteComponent.h"
#include "Component/MoveComponent.h"
#include "Core/Texture.h"

Ball::Ball(GameWorld* gameWorld):
	Actor(gameWorld)
{
	// Initialize to random position/orientation
	Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f),Vector2(512.0f, 384.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(gameWorld->GetTexture("Content/Character/Blue_Front1.png"));

	// Create a move Component
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);
	mc->SetAngularSpeed(1.f);

	// Add to mAsteroids in game
	gameWorld->AddBall(this);
}

Ball::~Ball()
{
	GetGameWorld()->RemoveBall(this);
}
