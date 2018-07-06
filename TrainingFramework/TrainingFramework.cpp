// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ObjShaders.h"
#include "EnvShaders.h"
#include "Globals.h"
#include "Texture.h"
#include "Model.h"
#include "Map.h"
#include <conio.h>

ObjShaders objShaders;
EnvShaders envShaders;

bool isKeyPressed = false;
unsigned char keyPressed;

Camera cam;
Matrix viewMatrix = Matrix().SetIdentity();
Matrix projectionMatrix = Matrix().SetPerspective(0.75f, static_cast<float>(Globals::screenWidth) / Globals::screenHeight, 0.1f, 100);

float mov = 0.1;
const int numberObjs = 2;
Object* object = new Object[numberObjs];
Map map;

ResourceManager* resouceManager;
SceneManager* sceneManager;

int Init(ESContext *esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	viewMatrix = cam.CalculateViewMatrix();

	object[0].SetTranslation(Vector3(0.25f, -0.5f, -1.0f));
	object[0].SetScale(Vector3(0.35, 0.35, 0.5));
	object[0].CalculateTransformMatrix();

	object[0].Init("../ResourcesPacket/Textures/Woman1.TGA", "../ResourcesPacket/Models/Woman1.NFG");

	object[1].SetTranslation(Vector3(-0.25f, -0.5f, -1.0f));
	object[1].SetScale(Vector3(0.35, 0.35, 0.5));
	object[1].CalculateTransformMatrix();
	object[1].Init("../ResourcesPacket/Textures/Woman2.TGA", "../ResourcesPacket/Models/Woman2.NFG");

	resouceManager = ResourceManager::GetInstance();
	sceneManager = SceneManager::GetInstance();

	//map.SetTranslation(Vector3(0.0f, 0.0f, 0.0f));
	//map.SetScale(Vector3(2, 2, 2));
	//map.CalculateTransformMatrix();
	//map.Init("../ResourcesPacket/Textures/Skybox/", "../ResourcesPacket/Models/SkyBox.NFG");

	//creation of shaders and program 
	//if (envShaders.Init("../Resources/Shaders/CubeSkypeVS.vs", "../Resources/Shaders/CubeSkypeFS.fs") != 0) return -1;
	return objShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw(ESContext *esContext) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < numberObjs; i++) {
		object[i].Draw(objShaders);
	}

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext *esContext, float deltaTime)
{
	if (isKeyPressed && deltaTime > 0) {
		if (keyPressed == 'A') cam.MoveAlongLocalX(-deltaTime);
		if (keyPressed == 'D') cam.MoveAlongLocalX(deltaTime);
		if (keyPressed == 'W') cam.MoveAlongLocalY(deltaTime);
		if (keyPressed == 'S') cam.MoveAlongLocalY(-deltaTime);
		if (keyPressed == 'Z') cam.MoveAlongLocalZ(deltaTime);
		if (keyPressed == 'X') cam.MoveAlongLocalZ(-deltaTime);
		if (keyPressed == 'R') cam.RotateAroundWorldY(deltaTime);
		if (keyPressed == 'T') cam.RotateAroundWorldY(-deltaTime);
		if (keyPressed == 'G') cam.RotateAroundLocalX(deltaTime);
		if (keyPressed == 'H') cam.RotateAroundLocalX(-deltaTime);
		if (keyPressed == 'K') cam.RotateAroundLocalZ(deltaTime);
		if (keyPressed == 'J') cam.RotateAroundLocalZ(-deltaTime);

		viewMatrix = cam.GetViewMatrix();
		for (int i = 0; i < numberObjs; i++) {
			object[i].CalculateTransformMatrix();
		}

	}
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		isKeyPressed = true;
		keyPressed = key;
	}
	else {
		isKeyPressed = false;
		keyPressed = '\0';
	}
}

void CleanUp()
{
	for (int i = 0; i < numberObjs; i++) {
		object[i].CleanUp();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	resouceManager->Init("../Resources/RM.txt");
	sceneManager->Init("../Resources/SM.txt");

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}