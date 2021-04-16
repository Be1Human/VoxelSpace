#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"


AnimSpriteComponent::AnimSpriteComponent(class Actor* Owner, int drawOrder /*= 100*/) :
	SpriteComponent(Owner, drawOrder),
	mAnimFPS(24),
	mCurrFrame(0)
{

}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size()>0) {

	}
}
