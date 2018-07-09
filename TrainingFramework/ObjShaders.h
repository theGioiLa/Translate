#pragma once
#include "Shaders.h"

class ObjShaders : public Shaders {
public:
	GLint positionAttribute, texcoordAttribute;
	GLint texcoordUniform, mvpUniform;

	void FindLocationUA();
};