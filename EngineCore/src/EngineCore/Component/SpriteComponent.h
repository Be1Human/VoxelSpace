#pragma once

#include "Component.h"
#include <GLFW/glfw3.h>

class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	virtual ~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:

	class Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
