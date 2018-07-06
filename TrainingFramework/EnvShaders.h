#pragma once
#include "Shaders.h"

class EnvShaders: public Shaders {
public:
	GLint positionAttribute;
	GLint mvp_matrix;

	void FindLocationUA() {
		positionAttribute = glGetAttribLocation(program, "a_pos");
		mvp_matrix = glGetUniformLocation(program, "mvp_matrix");
	}
};
