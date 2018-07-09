#pragma once
#include "../Utilities/utilities.h"
#include <vector>

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	GLuint m_Id;
	GLenum states;
	char* fileVS;
	char* fileFS;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	int Init();

	Shaders() {}
	Shaders(GLuint id,  GLenum enable_States = 0): 
		m_Id(id), states(enable_States) {
		fileVS = new char[50];
		fileFS = new char[50];
	}

	void CleanUp();
	
	void SetEnableState(GLenum enale_States) {
		states = enale_States;
	}

	~Shaders();
};