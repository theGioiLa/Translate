// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "ObjShaders.h"
#include "EnvShader.h"
#include "Globals.h"
#include "Texture.h"
#include "Model.h"
#include "Map.h"
#include <conio.h>

ObjShaders objShaders;
EnvShaders envShaders;
Matrix viewMatrix = Matrix().SetIdentity();
Matrix projectionMatrix = Matrix().SetPerspective(0.75f, static_cast<float>(Globals::screenWidth) / Globals::screenHeight, 0.1f, 100);
float mov = 0.1;
const int numberObjs = 4;
Object* object = new Object[numberObjs];
Map map;

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	object[0].SetTranslation(Vector3(1.0f, 0, -5.0f));
	object[0].SetScale(Vector3(0.55, 0.55, 0.5));
	object[0].CalculateTransformMatrix();

	object[0].Init("../ResourcesPacket/Textures/Woman1.TGA", "../ResourcesPacket/Models/Woman1.NFG") ;

	object[1].SetTranslation(Vector3(-1.0f, 0, -5.0f));
	object[1].SetScale(Vector3(0.5, 0.5, 0.5));
	object[1].CalculateTransformMatrix();
	object[1].Init("../ResourcesPacket/Textures/Woman2.TGA", "../ResourcesPacket/Models/Woman2.NFG");

	object[2].SetTranslation(Vector3(-1.5f, -0.5, -5.0f));
	object[2].SetScale(Vector3(0.5, 0.5, 0.5));
	object[2].CalculateTransformMatrix();
	object[2].Init("../ResourcesPacket/Textures/Woman1.TGA", "../ResourcesPacket/Models/Woman1.NFG");

	object[3].SetTranslation(Vector3(-2.5f, 0, -5.0f));
	object[3].SetScale(Vector3(0.5, 0.5, 0.5));
	object[3].CalculateTransformMatrix();
	object[3].Init("../ResourcesPacket/Textures/Woman1.TGA", "../ResourcesPacket/Models/Woman1.NFG");

	map.SetTranslation(Vector3(0.0f, 0.0f, -4.0f));
	map.SetScale(Vector3(0.5, 0.5, 0.5));
	map.CalculateTransformMatrix();
	map.Init("../ResourcesPacket/Textures/Skybox/", "../ResourcesPacket/Models/SkyBox.NFG");

	//creation of shaders and program 
	if (envShaders.Init("../Resources/Shaders/CubeSkypeVS.vs", "../Resources/Shaders/CubeSkypeFS.fs") != 0) return -1;
	return objShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw ( ESContext *esContext ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	map.Draw(envShaders);
	for (int i = 0; i < numberObjs; i++) {
		object[i].Draw(objShaders);
	}

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	object[0].SetRotationAngle(Vector3(0.0f, mov+=0.01, 0.0f));
	object[0].CalculateTransformMatrix();

	map.SetRotationAngle(Vector3(0.0f, mov, 0.0f));
	map.CalculateTransformMatrix();
}

void Key (ESContext *esContext, unsigned char key, bool bIsPressed)
{
	int count;
	glGetProgramiv(objShaders.program, GL_ACTIVE_UNIFORMS, &count);
	printf_s("%d ", count);

}

void CleanUp()
{
	for (int i = 0; i < numberObjs; i++) {
		object[i].CleanUp();
	}
	map.CleanUp();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc (&esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

