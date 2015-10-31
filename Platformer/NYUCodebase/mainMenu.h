#pragma once
#include "SheetSprite.h"


class MainMenu {
public:

	MainMenu();
	MainMenu(ShaderProgram *program);
	~MainMenu();

	GLuint LoadTexture(const char *image_path);

	ShaderProgram *programMenu;

	GLuint fontSpriteSheet = LoadTexture("pixel_font.png");

	void Render();
	void Update(float elapsed);

};