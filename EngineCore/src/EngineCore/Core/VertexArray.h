#pragma once


class VertexArray {

public:
	/*
	* verts:The Array of the Vertices£¨Vertices Coordinate Array)
	* numverts:Number of Vertices 
	* indices:The Array of the Index(Triangles Vertices Array)
	* numIndices:Number of Index 
	*/
	VertexArray(const float* verts,unsigned int numVerts,const unsigned int* indices ,unsigned int numIndices);
	~VertexArray();


	//Activate the Vertex Array to use it
	void SetActive();


	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	unsigned int mNumVerts; //Size of the Vertex Buffer

	unsigned int mNumIndices; //Size of the Index Buffer

	unsigned int mVertexArray;//The Vertex Array ID

	unsigned int mVertexBuffer;//The Vertex Buffer ID 

	unsigned int mIndexBuffer;//The Index Buffer ID


};
