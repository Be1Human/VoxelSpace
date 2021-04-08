#include "SpriteComponent.h"
#include "Shader.h"
#include "Actor.h"
#include "GameWorld.h"
#include <iostream>
#include "Random.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGameWorld()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGameWorld()->RemoveSprite(this);
}


void SpriteComponent::Draw(Shader* shader)
{
	//TEST LOG
	//cout << "TEST::Draw Actor" << mTexWidth << endl;

	// Scale the Quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(100),static_cast<float>(100),1.0f);
	Matrix4 world = scaleMat * mOwner->GetWorldTransform();

	// Set world transform
	shader->SetMatrixUniform("uWorldTransform", world);

	// Set current texture
	//mTexture->SetActive();

	// Draw Quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

