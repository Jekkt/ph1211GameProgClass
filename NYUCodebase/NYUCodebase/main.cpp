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
float lastFrameTicks = 0.0f;
float angle = 0;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
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

		
		

		GLuint skeletonTex = loadTexture("skeleton.png");
		GLuint nyanTex = loadTexture("nyan.png");
		GLuint eyeTex = loadTexture("eye.png");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		

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
				}
			}
		}

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;

		glClearColor(0.5f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		const Uint8 *keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_LEFT]) {
			//go left
			angle += elapsed;
		}
		else if (keys[SDL_SCANCODE_RIGHT]) {
			// go right
			angle -= elapsed;
		}

		

		projectionMatrix.setOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
		modelMatrix.identity();
		modelMatrix.Rotate(elapsed * (3.1415926f / 180.0f));

		program.setModelMatrix(modelMatrix);
		program.setProjectionMatrix(projectionMatrix);
		program.setViewMatrix(viewMatrix);

		glUseProgram(program.programID);

		

		
	
		//eye

		float vertices1[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f };
		//float vertices2[] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f };

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices1);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords1[] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords1);
		glEnableVertexAttribArray(program.texCoordAttribute);

		loadTexture("eye.png");

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//nyan

		float vertices3[] = { 1.5f, -0.5f, 1.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 1.5f, 0.5f };
		

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices3);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords3[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
		float texCoords4[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords3);
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords4);

		loadTexture("nyan.png");

		glDrawArrays(GL_TRIANGLES, 0, 3);

		//skeleton

		float vertices5[] = { -0.5f, -0.5f, -1.0f, 0.5f, -1.5f, -0.5f, -1.5f, 0.5f, -1.5f, -0.5f, -0.5f, 0.5f };
		//float vertices6[] = { -1.5f, 0.5f, -1.5f, -0.5f, -0.5f, 0.5f };
		
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices5);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords5[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
		float texCoords6[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords5);
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords6);

		loadTexture("skeleton.png");
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//test
		glBegin(GL_TRIANGLES);

		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);
		glVertex3f(1.0f, 2.0f, 0.0f);

		glEnd();

		
		


		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);
		
		SDL_GL_SwapWindow(displayWindow);
		lastFrameTicks = ticks;
	}

	SDL_Quit();
	return 0;
}


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