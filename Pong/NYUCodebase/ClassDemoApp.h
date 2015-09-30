#pragma once

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Matrix.h"
#include "ShaderProgram.h"

#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

class ClassDemoApp {

	public:

		ClassDemoApp();
		~ClassDemoApp();

		void Setup();

		void ProcessInput();
		void Render();
		void Update(float elapsed);

		GLuint loadTexture(const char *image);

		void DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY);

		void UpdateAndRender();

		bool isDone();

private:

	ShaderProgram *program;

	SDL_Joystick *joystick;
	SDL_Window* displayWindow;
	SDL_Event event;

	GLuint eyeTex;

	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	float lastFrameTicks = 0.0f;
	float angle = 0;
	bool done = false;

	float x_reso = 640.0f;
	float y_reso = 320.0f;

	float x_units = 3.55f;
	float y_units = 2.0f;

	float xDir = 0;
	float yDir = 0;

	float xPos = 0;
	float yPos = 0;

};