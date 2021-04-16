#include <string>
using namespace std;

class Texture {
public:
	Texture();
	~Texture();

	bool Load(const string& fileName);

	void Unload();

	void SetActive();
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:

	//OpenGL ID of this Texture
	unsigned int mTextureID;

	//The Width/Height of Texture
	int mWidth;
	int mHeight;


};