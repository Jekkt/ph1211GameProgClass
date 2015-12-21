#pragma once
#include "ClassDemoApp.h"

class gameOver
{
public:
	gameOver();
	gameOver(ShaderProgram *program);
	~gameOver();

	ShaderProgram *programOver;

	void DrawText(int fontTexture, std::string text, float size, float spacing);
	GLuint LoadTexture(const char *image_path);


	GLuint fontSpriteSheet = LoadTexture("pixel_font.png");
	GLuint alien = LoadTexture("sprites.png");
	GLuint eyeTex = LoadTexture("eye.png");
	GLuint dice = LoadTexture("diceRed.png");
	GLuint comicFont = LoadTexture("ComicFont.tga");

	void Render();
	void Update(float elapsed);

};

