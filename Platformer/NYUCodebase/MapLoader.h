#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Entity.h"

#include "ClassDemoApp.h"
#include "SheetSprite.h"

class MapLoader
{
public:

#define TILE_SIZE 32;

	#define LEVEL_WIDTH 25;
	#define LEVEL_HEIGHT 25;

	typedef unsigned char *charPtr;

	int mapWidth;
	int mapHeight;

	bool mapLoaded = false;

	charPtr *levelData;

	ShaderProgram *loaderProgram;

	std::vector<Entity*> entis;

	Entity entity;

	std::vector<Entity*> getEntities();

	MapLoader();
	MapLoader(ShaderProgram *program);
	~MapLoader();

	bool loadMap();

	bool readHeader(std::ifstream &stream);
	bool readLayerData(std::ifstream &stream);
	bool readEntityData(std::ifstream &stream);

	void placeEntity(std::string type, float placeX, float placeY);

	GLuint LoadTexture(const char *image_path);

	GLuint tileSprites = LoadTexture("platformertiles.png");
	GLuint characterSprites = LoadTexture("characters_3.png");

	SheetSprite *playerSprite;

	SheetSprite *invaderA0;
};

