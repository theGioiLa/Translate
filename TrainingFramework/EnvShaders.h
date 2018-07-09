#pragma once
#include "Shaders.h"

class EnvShaders: public Shaders {
public:
	GLint positionAttribute;
	GLint mvp_matrix;
	void FindLocationUA();
};