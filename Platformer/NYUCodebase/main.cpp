#include "ClassDemoApp.h"


// 60 FPS (1.0f/60.0f)

#define FIXED_TIMESTEP 0.0166666f;
#define MAX_TIMESTEPS 6;


/*

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

float lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 - v1*t;
}

void fixedUpdate(float elapsed) {
	

	velocity_x = acceleration_x * elapsed;
	velocity_y = acceleration_y * elapsed;

	velocity_x = lerp(velocity_x, 0.0f, elapsed*friction_x);
}

*/

int main(int argc, char *argv[])
{
	ClassDemoApp app;
	while(!app.UpdateAndRender()){}
		return 0;
	}

