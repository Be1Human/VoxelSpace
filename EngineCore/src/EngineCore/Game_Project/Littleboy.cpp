#include "Littleboy.h"
#include "Component/AnimSpriteComponent.h"
#include "GameWorld.h"
#include "Component/InputComponent.h"

Littleboy::Littleboy(class GameWorld* gameWorld):
	Actor(gameWorld)
{

	//Create A Animation Sprite Component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	asc->SetAnimFPS(15);
	vector<Texture*> anims = {
		gameWorld->GetTexture("D:/VoxelSpace/VoxelSpace/EngineCore/Content/Character/LittleBoy//Blue_Right1.png"),
		gameWorld->GetTexture("D:/VoxelSpace/VoxelSpace/EngineCore/Content/Character/LittleBoy//Blue_Right2.png"),
		gameWorld->GetTexture("D:/VoxelSpace/VoxelSpace/EngineCore/Content/Character/LittleBoy//Blue_Right3.png"),
	};
	asc->SetAnimTextures(anims);

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(GLFW_KEY_D);
	ic->SetBackKey(GLFW_KEY_A);
	ic->SetMaxForwardSpeed(300.0f);

	// 
}

void Littleboy::UpdateCharacter(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

}
