#pragma once
#include "SpriteComponent.h"
#include "Core/Texture.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {

public:
	AnimSpriteComponent(class Actor* Owner , int drawOrder = 100);

	//Update animation every frame
	void Update(float deltaTime) override;


	//Set the Texture for Animation
	void SetAnimTextures(const vector<Texture*>& textures);

	//Set/Get the Animation FPS
	float GetAnimFPS() const { return mAnimFPS; }

	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	//All AnimTextures
	vector<Texture*> mAnimTextures;

	//Current Frame Displayed
	float mCurrFrame;

	//Animation frame rate
	float mAnimFPS;
};