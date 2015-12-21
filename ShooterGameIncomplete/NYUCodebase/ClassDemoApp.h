
#pragma once

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Matrix.h"
#include "ShaderProgram.h"

#include "gameLevel.h"
#include "gameOver.h"
#include "TitleMenu.h"

#include <SDL_mixer.h>

#include "SheetSprite.h"

//tilemaps


#include <math.h>
#include <vector>
#include "Vector3.h"

#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

class ClassDemoApp {

public:

		ClassDemoApp();
		~ClassDemoApp();

		bool doublejump = false;

		void placeEntity(std::string type, float placeX, float placeY);

		void Setup();

		Mix_Chunk *jumpSound;
		Mix_Chunk *bgMus;

		void ProcessInput();
		void Render();
		void Update(float elapsed);
		void FixedUpdate();

		GLuint LoadTexture(const char *image);

		ShaderProgram *program;
		
		float elapsedTime;

		float x_reso = 800.0f;
		float y_reso = 800.0f;

		bool isShooting;

		bool leftIsPressed;
		bool rightIsPressed;

		bool isJumping;

		Vector3 camRot;

		int score;
		int life;

		GLuint frameBuffer;
		
		Matrix projectionMatrix;
		Matrix modelMatrix;
		Matrix viewMatrix;

		Vector3 vector;
		

		enum GameState{ STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER };

		int state = STATE_GAME_LEVEL;

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

	bool musicIsPlaying;

	

	float ortho_width = 8.0f;
	float ortho_height = 8.0f;

	float units_x = (x_reso * ortho_width) - ortho_width / 2.0f;
	float units_y = (y_reso * ortho_height) - ortho_height / 2.0f;

	float xDir = 0;
	float yDir = 0;

#define FIXED_TIMESTEP 0.0166666f;
#define MAX_TIMESTEPS 6;
	float timeLeftOver = 0.0f;
	float xPos = 0;
	float yPos = 0;

	float elapsed;

};