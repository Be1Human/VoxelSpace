#include <glad/glad.h>
#include "SpriteComponent.h"
#include "Core/Shader.h"
#include "Core/Actor.h"
#include "Game_Project/GameWorld.h"
#include <iostream>
#include "Math/Random.h"
#include "Core/Texture.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
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
	if (mTexture) {
		//TEST LOG
		//cout << "TEST::Draw Actor" << mTexWidth << endl;

		// Scale the Quad by the width/height of texture
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		// Set world transform
		shader->SetMatrixUniform("uWorldTransform", world);


		// Set current texture
		mTexture->SetActive();

		// Draw Quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	//Set Width/Height
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}

