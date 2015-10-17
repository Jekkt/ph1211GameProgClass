#pragma once
#include "ClassDemoApp.h"
#include "Entity.h"
#include "SheetSprite.h"

class gameLevel
{
public:
	gameLevel();
	gameLevel(ShaderProgram *program);
	~gameLevel();

	bool gameIsOver;

	int score;

	int accumulator = 39;

	void DrawText(int fontTexture, std::string text, float size, float spacing);

	GLuint LoadTexture(const char *image_path);

	ShaderProgram *programLevel;

	GLuint spaceSprites = LoadTexture("sprites.png");
	GLuint dice = LoadTexture("diceRed.png");
	GLuint comicFont = LoadTexture("ComicFont.tga");

	SheetSprite playerSprite = SheetSprite(programLevel, spaceSprites, 0, 0, 60.0f / 256.0f, 32.0f / 128.0f, 1.0f);

	SheetSprite invaderA0 =  SheetSprite(programLevel, spaceSprites, 62.0f, 0.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.0f);
	SheetSprite invaderB0 = SheetSprite(programLevel, spaceSprites, 50.0f, 68.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.0f);
	SheetSprite invaderC0 = SheetSprite(programLevel, spaceSprites, 100.0f, 34.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.0f);
	SheetSprite bulletSprite = SheetSprite(programLevel, spaceSprites, 0.0f / 256.0f, 0.0f / 128.0f, 1.0f / 256.0f, 3.0f / 128.0f, 0.2f);

	Entity *player;
	Entity *invaderA[13];
	Entity *invaderB[13];
	Entity *invaderC[13];

	Entity *bullets[14];

	void Render();
	void Update(float elapsed);
};

