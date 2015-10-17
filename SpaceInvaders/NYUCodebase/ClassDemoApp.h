
#pragma once

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Matrix.h"
#include "ShaderProgram.h"

#include "gameLevel.h"
#include "gameOver.h"
#include "TitleMenu.h"

#include "SheetSprite.h"

#include <vector>

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
		void FixedUpdate();

		GLuint LoadTexture(const char *image);

		ShaderProgram *program;
		
		float elapsedTime;

		bool isShooting;

		bool leftIsPressed;
		bool rightIsPressed;

		int score;
		int life;


		
		Matrix projectionMatrix;
		Matrix modelMatrix;
		Matrix viewMatrix;

		enum GameState{ STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER };

		int state = STATE_MAIN_MENU;

		void DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY);

		bool UpdateAndRender();

		bool isDone();

private:


	SDL_Joystick *joystick;
	SDL_Window* displayWindow;
	SDL_Event event;

	GLuint eyeTex;

	

	float lastFrameTicks = 0.0f;
	float angle = 0;
	bool done = false;

	float x_reso = 800.0f;
	float y_reso = 800.0f;

	float x_units = 4.0f;
	float y_units = 4.0f;

	float xDir = 0;
	float yDir = 0;



	float xPos = 0;
	float yPos = 0;

	

};