#include "mainMenu.h"

MainMenu::MainMenu() {
	
	//fontSpriteSheet = LoadTexture("SpriteImages/pixel_font.png");
	
}

MainMenu::MainMenu(ShaderProgram *program) {

	//fontSpriteSheet = LoadTexture("SpriteImages/pixel_font.png");
	programMenu = program;
}

MainMenu::~MainMenu() {

}

void MainMenu::Render() {

	std::vector<SheetSprite>;
	if (fontSpriteSheet) {
		SheetSprite letter = SheetSprite(programMenu, fontSpriteSheet, 0 / 127.0f, 0 / 127.0f, 10, 10, 1.0f);

		letter.Draw();
	}
}

void MainMenu::Update(float elapsed) {

}

GLuint MainMenu::LoadTexture(const char *image_path) {
	if (image_path) {
		SDL_Surface *surface = IMG_Load(image_path);

		GLuint textureID;

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);
		if (surface) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			SDL_FreeSurface(surface);

			std::cout << "Texture was succesfully loaded!" << std::endl;

			return textureID;
		}
		else { 
			std::cout << "Texture couldn't be loaded!" << std::endl;
			return 0; }
	}

	return 0;

}
