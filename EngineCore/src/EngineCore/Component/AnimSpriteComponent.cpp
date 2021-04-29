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
		//Update the Current frame based on frame rate and delta time
		//EX:Let Animation limited to 24FPS whatever Game FPS
		mCurrFrame += mAnimFPS * deltaTime;

		//Wrap current frame if needed
		if(mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame =0;
		}

		//Set the current Texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const vector<Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0) {
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);  //Set the First Animation Texture
	}
}



