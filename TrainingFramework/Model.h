#pragma once
#include "GLES2\gl2.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model {
	Vertex* m_pVertices;
	int* m_pIndex;
	GLint m_Id;


public:
	unsigned int m_nIndices, m_nVertices;
	GLuint m_vboId, m_iboId;

	Model(GLuint nVertices, GLuint nIndices);
	Model() {}

	void Init(char* filename);
	void BindData();
	void CleanUp();
	void SetVertices(Vertex* vertices) { m_pVertices = vertices; }
};