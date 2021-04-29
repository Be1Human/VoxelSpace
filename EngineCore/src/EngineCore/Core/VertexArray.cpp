#include <glad/glad.h>
#include "VertexArray.h"


VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts), mNumIndices(numIndices)
{
	/*
	* glGenBuffers(Number of Objects , &(Buffer Objects Name))
	*/

	//Create and Bind Vertex Array Object
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//Create Vertex Buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW); //Copy Data from verts to GL_ARRAY_BUFFER  

	//Create Index Buffer
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);  //Copy Data from indices to GL_ELEMENT_ARRAY_BUFFER  

	//Specify the Vertex Attributes, Aims to tell OpenGL how to parse vertices data
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(
		0,                   //Attribute index£¬0 means only have Location(have no RGB)
		3,                   //Number of Components
		GL_FLOAT,            //Type of the Components
		GL_FALSE,           //Used for Integral
		sizeof(float) * 5,  //The Size of the Vertex(Used to find the Correct Offset,Stride)
		(void*)0            //The begin Offset of the Data in the Buffer
	);

	//Texture Attributes Set
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,reinterpret_cast<void*>(sizeof(float) * 3));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Draw in wire frame polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

VertexArray::~VertexArray()
{
	
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);

}
