#pragma  once
#include<string>
#include "Math/Math.h"

using namespace std;

class Shader {

public:
	Shader();
	~Shader();

	//Load the Vertex/fragment shaders And Link them
	bool Load(const string& vertName,const string& fragName);
	void Unload();

	//Activate shader Programs
	void SetActive();

	//Set The Shader Uniform
	void SetMatrixUniform(const char* name, const Matrix4& matrix);

private:

	//Tries to Compile Specify Shader Name
	bool CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader);

	//Test Whether vertex/fragment compile Successfully
	bool IsCompiled(GLuint shader);

	//Test Whether vertex/fragment programs Link
	bool IsVaildProgram();


	//The Shader IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;

};