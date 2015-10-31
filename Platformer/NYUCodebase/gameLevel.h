#pragma once
#include "ClassDemoApp.h"
#include "Entity.h"
#include "SheetSprite.h"
#include "MapLoader.h"

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

	GLuint tileSprites = LoadTexture("platformertiles.png");
	GLuint characterSprites = LoadTexture("characters_3.png");

	SheetSprite *playerSprite;

	SheetSprite *invaderA0;

	std::vector<Entity*> entities;



	Entity *player;
	Entity *test;
	Entity *invaderA[13];

	Entity *bullets[14];

	void Render();
	void Update(float elapsed);
};

