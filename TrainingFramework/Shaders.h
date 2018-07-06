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
	virtual void FindLocationUA() {};

	Shaders() {}
	Shaders(GLuint id, char* _fileVS, char* _fileFS, GLenum enable_States) :
		m_Id(id), fileVS(_fileVS), fileFS(_fileFS), states(enable_States) {}

	~Shaders();
};