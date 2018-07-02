#pragma once 
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Camera {
protected:
	Matrix viewMatrix = Matrix().SetIdentity();

};