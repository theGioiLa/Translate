#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];

	int Init(char * fileVertexShader, char * fileFragmentShader);
	virtual void FindLocationUA() = 0;
	~Shaders();
};