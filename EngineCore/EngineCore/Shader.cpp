#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


Shader::Shader():
	mVertexShader(0),
	mFragShader(0),
	mShaderProgram(0)
{

}

Shader::~Shader()
{

}

bool Shader::Load(const string& vertName, const string& fragName)
{
	//Compile And Check Vertex And FragMent Shader
	if (!CompileShader(vertName,GL_VERTEX_SHADER, mVertexShader)||
		!CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader)) {
		return false;
	}

	//Create A Shader Program And Link Shaders
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	//Verify the Shader Program Link Successfully
	if (!IsVaildProgram()) {
		return false;
	}

	return true;

}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mVertexShader);

}

void Shader::SetActive()
{
	
	//cout << "Set mShaderProgram" << endl;
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{

	//Find the uniform by this name And Store it
	GLuint loc = glGetUniformLocation(mShaderProgram, name);

	//Send the Matrix data to the Uniform(In Shaders)
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());

}

bool Shader::CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader)
{
	//Open File
	ifstream shaderFile;
	shaderFile.open(fileName);

	//Open And Compile File
	if (shaderFile.is_open()) {
		//Read All Code into a string
		stringstream sstream;
		sstream << shaderFile.rdbuf();  //
		string contents = sstream.str();
		//Get the C type Char Pointer
		const char* contentChar = contents.c_str();

		//Create Specify Shader Object
		outShader = glCreateShader(shaderType);

		//Set the Shader
		glShaderSource(outShader,1 ,&contentChar,nullptr);

		//Compile Shader
		glCompileShader(outShader);

		if (!IsCompiled(outShader)) {
			cout << "ERROR::Faild to Compiled Shader" << endl;
			return false;
		}
	}
	else {
		cout << "ERROR::Shader file not fount:"<< fileName .c_str()<< endl;
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	
	GLint status;
	//Check and Get the Compile Status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (!status) {
		char infoLog[512];
		//Get the Failed Info
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		cout << "ERROR::GLSL Compile Failed:\n" << infoLog << endl;
		return false;
	}

	return true;
}

bool Shader::IsVaildProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgram,GL_LINK_STATUS,&status);

	//If Failed
	if (!status) {
		char infoLog[512];
		////Get the Failed Info
		glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
		cout << "ERROR::Linking Failed:\n" << infoLog << endl;
		return false;
	}

	return true;
}

