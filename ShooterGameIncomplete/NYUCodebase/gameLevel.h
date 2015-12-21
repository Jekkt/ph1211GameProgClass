#pragma once
#include "ClassDemoApp.h"
#include "Entity.h"
#include "SheetSprite.h"
#include "MapLoader.h"
#include "Vector3.h"

class gameLevel
{
public:
	gameLevel();
	gameLevel(ShaderProgram *program);
	~gameLevel();

	

	bool gameIsOver;

	int score;

	int accumulator = 39;

	float yaw;

	void DrawText(int fontTexture, std::string text, float size, float spacing);

	GLuint LoadTexture(const char *image_path);

	ShaderProgram *programLevel;

	GLuint spaceSprites = LoadTexture("sprites.png");
	GLuint dice = LoadTexture("diceRed.png");
	GLuint comicFont = LoadTexture("ComicFont.tga");

	GLuint tileSprites = LoadTexture("SpookySpriteSheet.png");
	GLuint characterSprites = LoadTexture("characters_3.png");

	GLuint shottySprite = LoadTexture("shottyGun.png");

	SheetSprite *playerSprite;

	SheetSprite *invaderA0;

	std::vector<Entity*> entities;

	

	Entity *player;
	Entity *player1;
	Entity *invaderA[13];

	Entity *bullets[14];

	void Render();
	void Update(float elapsed);
};

