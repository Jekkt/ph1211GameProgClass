#include "gameLevel.h"

MapLoader *mapLoader;


gameLevel::gameLevel()
{
	player = new Entity();
}

gameLevel::gameLevel(ShaderProgram *program)
{
	programLevel = program;
	player = new Entity(programLevel);
	
	mapLoader = new MapLoader(programLevel);

	mapLoader->mapLoaded = mapLoader->loadMap();

	playerSprite = new SheetSprite(programLevel, characterSprites, 0, 0, 32.0f / 256.0f, 32.0f / 128.0f, 1.0f);

	invaderA0 = new SheetSprite(programLevel, tileSprites, 0.0f, 0.0f, 32.0f / 256.0f, 32.0f / 96.0f, 1.0f);

	test = new Entity(ENTITY_PLAYER, 0.5f, -9.5f, playerSprite);

	test->width = 0.1f;
	test->height = 1.0f;

	int mapWidth = mapLoader->mapWidth;
	int mapHeight = mapLoader->mapHeight;

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (mapLoader->levelData[y][x] > 0) {

				Entity *ent = new Entity(ENTITY_TILES, (((float)x*0.39f)), (float)-y*1.0f, invaderA0);

				ent->width = 0.3f;
				ent->height = 1.0f;

				mapLoader->entis.push_back(ent);

			}

		}
	}

}


gameLevel::~gameLevel()
{
	delete player;


}

void gameLevel::Render() {

	Matrix modelMatrix;
	Matrix viewMatrix;

	if (mapLoader->mapLoaded) {

		modelMatrix.identity();
		modelMatrix.Translate(0, 0, 0);
		modelMatrix.Rotate(90.0f);
		programLevel->setModelMatrix(modelMatrix);
		
		entities = mapLoader->getEntities();

		for (auto &entity : entities) {
			entity->programEnt = programLevel;
			entity->render(programLevel);
			if (entity->type == ENTITY_PLAYER) {
				player = entity;
				//viewMatrix.Translate(entity->yPos, entity->xPos, 0);
				//programLevel->setViewMatrix(viewMatrix);
			}
		}
		modelMatrix.identity();
		modelMatrix.Translate(-40, -40, 0);
		programLevel->setModelMatrix(modelMatrix);

	}

	modelMatrix.identity();
	modelMatrix.Translate(0, 0, 0);
	programLevel->setModelMatrix(modelMatrix);
	
	test->render(programLevel);

}

void gameLevel::Update(float elapsed) {
	Matrix viexMatrix;
	
	viexMatrix.Translate(-test->xPos, -test->yPos, 0);
	programLevel->setViewMatrix(viexMatrix);

	entities = mapLoader->getEntities();

	for (auto &entity : entities) {	
		test->collideWith(entity);
	}

	
	

	player->update(elapsed);
	test->update(elapsed);


	
}

GLuint gameLevel::LoadTexture(const char *image_path) {

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

void gameLevel::DrawText(int fontTexture, std::string text, float size, float spacing) {
	float texture_size = 1.0f / 16.0f;
	std::vector<float> vertexData;
	std::vector<float> texCoordData;

	for (int i = 0; i < text.size(); i++) {
		//std::cout << text[i] + ": " <<(int)text[i] << std::endl;
		float texture_x = (float)(((int)text[i] % 16) / 16.0f);
		float texture_y = (float)(((int)text[i] / 16) / 16.0f);
		vertexData.insert(vertexData.end(), {
			((size + spacing) * i) + (-0.5f * size), 0.5f * size,
			((size + spacing) * i) + (-0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), 0.5f * size,
			((size + spacing) * i) + (0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), 0.5f * size,
			((size + spacing) * i) + (-0.5f * size), -0.5f * size,
		});
		texCoordData.insert(texCoordData.end(), {
			texture_x, texture_y,
			texture_x, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x + texture_size, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x, texture_y + texture_size
		});

	}
	glUseProgram(programLevel->programID);

	glVertexAttribPointer(programLevel->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
	glEnableVertexAttribArray(programLevel->positionAttribute);

	glVertexAttribPointer(programLevel->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
	glEnableVertexAttribArray(programLevel->texCoordAttribute);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

	glDisableVertexAttribArray(programLevel->positionAttribute);
	glDisableVertexAttribArray(programLevel->texCoordAttribute);
}
