// TrainingFramework.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "ResourceManager.h"
#include "SceneManager.h"
#include <conio.h>

bool isKeyPressed = false;
unsigned char keyPressed;

SceneManager* sceneManager;
ResourceManager* resourceManager;

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	sceneManager = SceneManager::GetInstance();
	resourceManager = ResourceManager::GetInstance();

	if (resourceManager->Init("../Resources/RM.txt") != 0) return -1;
	return sceneManager->Init("../Resources/SM.txt");
} 

void Draw ( ESContext *esContext ) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sceneManager->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	if (isKeyPressed && deltaTime > 0) {
		sceneManager->Update(keyPressed, deltaTime);
	}
}

void Key (ESContext *esContext, unsigned char key, bool bIsPressed)
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
	resourceManager->CleanUp();
	sceneManager->CleanUp();

	delete resourceManager;
	delete sceneManager;
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

