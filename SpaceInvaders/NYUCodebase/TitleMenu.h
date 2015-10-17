#pragma once

#include "ClassDemoApp.h"

class TitleMenu
{
public:
	TitleMenu();
	TitleMenu(ShaderProgram *program);
	~TitleMenu();
	void DrawText(int fontTexture, std::string text, float size, float spacing);

	GLuint LoadTexture(const char *image_path);

	bool alternate = false;

	float timePassed;

	ShaderProgram *programMenu;

	
	GLuint fontSpriteSheet = LoadTexture("pixel_font.png");
	GLuint alien = LoadTexture("sprites.png");
	GLuint eyeTex = LoadTexture("eye.png");
	GLuint dice = LoadTexture("diceRed.png");
	GLuint comicFont = LoadTexture("ComicFont.tga");

//	std::vector<SheetSprite> Fonts;
	int letters[16][16];

	void Render();
	void Update(float elapsed);
};

