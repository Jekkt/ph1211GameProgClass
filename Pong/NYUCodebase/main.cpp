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



SDL_Window* displayWindow;
GLuint loadTexture(const char *image_path);

//Time and things
float lastFrameTicks = 0.0f;
float angle = 0;

// GameObjects and things
float ballSpeedX = 2.0f;
float ballSpeedY = 0.5f;

float ballPosX = 0;
float ballPosY = 0;

float ballSize = 0.30f;

float paddle1Width = 0.25f;
float paddle1Height = 2.0f;
float paddle1PosX = -2.875f;
float paddle1PosY = 0;

float paddle2Width = 0.25f;
float paddle2Height = 2.0f;
float paddle2PosX = 2.875;
float paddle2PosY = 0;


//mouse and coordinate system of game field
float unitX = 0;
float unitY = 0;

float positionX = 0;
float positionY = 0;

float x_reso = 640.0f;
float y_reso = 320.0f;

float x_units = 3.55f;
float y_units = 2.0f;

/*

units_x 
units_y = ((y_resolution

*/

GLuint loadTexture(const char *image_path) {

	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;

}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	//SDL_Joystick *joystick = SDL_JoystickOpen(0);

	displayWindow = SDL_CreateWindow("Pong Extreme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif




	glViewport(0, 0, 640, 360);

	ShaderProgram program(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	//GLuint birdTex = loadTexture("bird.png");
	//GLuint duckTex = loadTexture("duck.png");
	GLuint eyeTex = loadTexture("eye.png");

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					angle = 0.0f;
					std::cout << "Space pressed!" << std::endl;
				}
			}
			else if (event.type == SDL_MOUSEMOTION) {

				unitX = (((float)event.motion.x / x_reso) * x_units) - x_units / 2.0f;
				unitY = (((float)(y_reso - event.motion.y) / y_reso) * y_units) - y_units / 2.0f;

				positionX = unitX;
				positionY = unitY;


			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {

				angle += 3.1415926536f * 0.25f;

			}
			else if (event.type == SDL_JOYAXISMOTION) {
				if (event.jaxis.which == 0) {
					if (event.jaxis.axis == 0) {
						float floatVal = ((float)event.jaxis.value) / 32767.0f;
						//ADD fabs threshold
						float xDir = floatVal;
					}
					else if (event.jaxis.axis == 1) {
						float floatVal = ((float)event.jaxis.value) / 32767.0f;
						//ADD fabs threshold
						float yDir = floatVal;
					}
				}
			}
			else if (event.type == SDL_JOYBUTTONDOWN) {

				if (event.jbutton.button == 0) {
					//turn turn quarter pi

				}


			}

		}
			
			float ticks = (float)SDL_GetTicks() / 1000.0f;
			float elapsed = ticks - lastFrameTicks;
			lastFrameTicks = ticks;

			paddle2PosY = positionY;
			 
			// game logic BEGIN

			
			
			if(ballPosX-ballSize/2 < paddle1PosX + paddle1Width/2 
				&& paddle1PosY + paddle1Height / 2 > ballPosY > paddle1PosY - paddle1Height / 2){
				ballSpeedX = -(ballSpeedX + 1);
			}
				
			if (ballPosX + ballSize/2 > paddle2PosX - paddle2Width/2
				&& paddle2PosY + paddle2Height / 2 > ballPosY 
				&& ballPosY > paddle2PosY - paddle2Height / 2) {
				ballSpeedX = -(ballSpeedX + 1);
			}
			

			if (ballPosY > 1.9f || ballPosY < -1.9f) {
				ballSpeedY = -ballSpeedY;
			} 
			
			if(ballPosX > 3.50f) {
				//lose player1
				std::cout << "Player on the right hand has lost!" << std::endl;
				ballPosX = 0.0f;
				ballPosY = 0.0f;
				ballSpeedX = -2.0f;
				ballSpeedY = -0.5f;
			}
			else if (ballPosX < -3.50f) {
				//lose player2
				std::cout << "Player on the left hand has lost!" << std::endl;
				ballPosX = 0.0f;
				ballPosY = 0.0f;
				ballSpeedX = 2.0f;
				ballSpeedY = 0.5f;
			}

				ballPosX += ballSpeedX * elapsed;
				ballPosY += ballSpeedY * elapsed;


				/* stuff for look up
				projectionMatrix.setOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
				float paddleWidth = 0.25f;
				float paddle1Height = 2.0f;
				float paddle1PosX = -2.875f;
				float paddle1PosY = 0;
				float paddle2Width = 0.25f;
				float paddle2Height = 2.0f;
				float paddle2PosX = 2.875f;
				float paddle2PosY = 0;
				*/


				//game logic END

			glClearColor(0.5f, 0.5f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			const Uint8 *keys = SDL_GetKeyboardState(NULL);

			if (keys[SDL_SCANCODE_LEFT]) {
				//go left
				std::cout << "Pressing Left" << std::endl;
				angle += elapsed;
			}
			else if (keys[SDL_SCANCODE_RIGHT]) {
				// go right
				std::cout << "Pressing Right" << std::endl;
				angle -= elapsed;
			}



			projectionMatrix.setOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
			modelMatrix.identity();

			angle = elapsed * (3.1415926f / 180.0f);

			//modelMatrix.Rotate(angle);
			//modelMatrix.Translate(0, positionY, 0);

			program.setModelMatrix(modelMatrix);
			program.setProjectionMatrix(projectionMatrix);
			program.setViewMatrix(viewMatrix);

			glUseProgram(program.programID);

			modelMatrix.Translate(0, ballPosY, 0);
			program.setModelMatrix(modelMatrix);
			

			float paddle1[] = { -3.0f, 1.0f, -3.0f, -1.0, -2.75f, 1.0f, -2.75f, -1.0f, -2.75f, 1.0f, -3.0f, -1.0f };

			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddle1);
			glEnableVertexAttribArray(program.positionAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			modelMatrix.identity();
			modelMatrix.Translate(0, positionY, 0);
			program.setModelMatrix(modelMatrix);

			

			float paddle2[] = { 2.75f, 1.0f, 2.75f, -1.0, 3.0f, 1.0f, 3.0f, -1.0f, 3.0f, 1.0f, 2.75f, -1.0f };
			//float paddle2[] = { 2.75f, 1.0f, 2.75f, -1.0, 3.0f, 1.0f, 3.0f, -1.0f, 3.0f, 1.0f, 2.75f, -1.0f };

			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddle2);
			glEnableVertexAttribArray(program.positionAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			modelMatrix.identity();
			modelMatrix.Translate(ballPosX, ballPosY, 0);
			program.setModelMatrix(modelMatrix);

			float ball[] = {-0.15f, 0.15f, -0.15f, -0.15f, 0.15f, 0.15f, 0.15f, -0.15f, 0.15f, 0.15f, -0.15f, -0.15f};

			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, ball);
			glEnableVertexAttribArray(program.positionAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(program.positionAttribute);
			glDisableVertexAttribArray(program.texCoordAttribute);

		

			SDL_GL_SwapWindow(displayWindow);

		}

		//SDL_JoystickClose(0);

		SDL_Quit();
		return 0;
	}

