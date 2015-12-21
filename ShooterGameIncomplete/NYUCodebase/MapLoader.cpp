#include "MapLoader.h"



MapLoader::MapLoader()
{

}

MapLoader::MapLoader(ShaderProgram *program)
{
	loaderProgram = program;

	playerSprite = new SheetSprite(loaderProgram, characterSprites, 0, 0, 32.0f / 256.0f, 32.0f / 128.0f, 1.0f);

	invaderA0 = new SheetSprite(loaderProgram, tileSprites, 62.0f, 0.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.0f);
}

MapLoader::~MapLoader()
{
}

bool MapLoader::readHeader(std::ifstream &stream) {
	std::string line;
	mapWidth = -1;
	mapHeight = -1;
	
	while (std::getline(stream, line)) {
		if (line == "") { break; }

		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);

		if (key == "width") {
			mapWidth = atoi(value.c_str());
		}
		else if (key == "height") {
			mapHeight = atoi(value.c_str());
		}
	}

	if (mapWidth == -1 || mapHeight == -1) {
		return false;
	}
	else {
		levelData = new unsigned char*[mapHeight]();
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}

bool MapLoader::readEntityData(std::ifstream &stream) {

	std::string line;
	std::string type;

	while (std::getline(stream, line)) {
		if (line == "") { break; }

		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);

		if (key == "type") {
			type = value;
		}
		else if (key == "location") {

			std::istringstream lineStream(value);
			std::string xPosition, yPosition;
			std::getline(lineStream, xPosition, ',');
			std::getline(lineStream, yPosition, ',');

			float placeX = (float)std::atoi(xPosition.c_str()) / 16.0f * TILE_SIZE;
			float placeY = (float)std::atoi(yPosition.c_str()) / 16.0f * -TILE_SIZE;

			placeEntity(type, placeX, placeY);

		}
	}
	return true;
}

bool MapLoader::readLayerData(std::ifstream &stream) {
	std::string line;
	while (std::getline(stream, line)) {
		if (line == "") { break; }
		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				std::getline(stream, line);
				std::istringstream lineStream(line);
				std::string tile;

				for (int x = 0; x < mapWidth; x++) {
					std::getline(lineStream, tile, ',');
					unsigned char val = (unsigned char)atoi(tile.c_str());
					if (val > 0) {
						levelData[y][x] = val - 1;
					}
					else {
						levelData[y][x] = 0;
					}
				}
			}
		}
	}
	return true;
}

bool MapLoader::loadMap() {
	std::ifstream infile{ "SpookyMap.txt" };
	std::string line;

	std::cout << "Loading map." << std::endl;

	while (std::getline(infile, line)) {
		if (line == "[header]") {
			std::cout << "Reading header." << std::endl;
			if (!readHeader(infile)) {
				return false;
			}
		}
		else if (line == "[layer]") {
			std::cout << "Reading Layer." << std::endl;
			readLayerData(infile);
		}
		else if (line == "[ObjectsLayer]"){
			std::cout << "Reading Entity." << std::endl;
			readEntityData(infile);
		}
	}

	return true;
}

void MapLoader::placeEntity(std::string type, float placeX, float placeY) {

	EntityType typeSwitch;

	Entity *ent = new Entity(loaderProgram);

	entity = *new Entity();

	ent->xPos = placeX;
	ent->yPos = placeY;

	//enum EntityType { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET, ENTITY_BULLET_PLAYER, ENTITY_BACKGROUND, ENTITY_MOON, ENTITY_TILES };

	if (type == "ENTITY_PLAYER") {
		typeSwitch = ENTITY_PLAYER;
		ent->sprite = *playerSprite;
	}
	else if (type == "ENTITY_BACKGROUND") {
		typeSwitch = ENTITY_BACKGROUND;
		ent->sprite = *playerSprite;
	}
	else if (type == "ENTITY_MOON") {
		typeSwitch = ENTITY_MOON;
		ent->sprite = *playerSprite;
	}
	else if (type == "ENTITY_TILES") {
		typeSwitch = ENTITY_TILES;
		ent->sprite = *playerSprite;
	}
	ent->type = typeSwitch;

	entis.reserve(1);
	//entis.push_back(new Entity(typeSwitch,placeX, placeY, playerSprite));
	entis.push_back(ent);
}

std::vector<Entity*> MapLoader::getEntities(){
	return entis;
}

GLuint MapLoader::LoadTexture(const char *image_path) {

	if (image_path) {
		SDL_Surface *surface = IMG_Load(image_path);

		GLuint textureID;

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);
		if (surface) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			SDL_FreeSurface(surface);

			std::cout << "Texture was succesfully loaded!" << std::endl;

			return textureID;
		}
		else {
			std::cout << "Texture couldn't be loaded!" << std::endl;
			return 0;
		}
	}

	return 0;
}