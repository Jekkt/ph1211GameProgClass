#include "gameLevel.h"



gameLevel::gameLevel()
{
	player = new Entity();
}

gameLevel::gameLevel(ShaderProgram *program)
{
	programLevel = program;
	player = new Entity(programLevel);
	
	for (int i = 0; i < 13; i++) {

		invaderA[i] = new Entity(programLevel);
		invaderB[i] = new Entity(programLevel);
		invaderC[i] = new Entity(programLevel);
		bullets[i] = new Entity(programLevel);

	}
	bullets[13] = new Entity(programLevel);
	
	//entities.push_back(player);
	playerSprite = SheetSprite(programLevel, spaceSprites, 0, 0, 60.0f / 256.0f, 32.0f / 128.0f, 0.2f);
	//player.setSprite(playerSprite);
	player->sprite = playerSprite;
	player->type = ENTITY_PLAYER; 
	player->yPos -= 1.8f;


	SheetSprite *invaderA0 = new SheetSprite(programLevel, spaceSprites, 62.0f/256.0f, 0.0f / 128.0f, 48.0f / 256.0f, 32.0f / 128.0f, 0.2f);
	SheetSprite *invaderB0 = new SheetSprite(programLevel, spaceSprites, 50.0f/256.0f, 68.0f/128.0f, 48.0f / 256.0f, 32.0f / 128.0f, 0.2f);
	SheetSprite *invaderC0 = new SheetSprite(programLevel, spaceSprites, 100.0f/256.0f, 34.0f / 128.0f, 48.0f / 256.0f, 32.0f / 128.0f, 0.2f);

	SheetSprite *bulletSprite = new SheetSprite(programLevel, spaceSprites, 1.0f / 256.0f, 1.0f / 128.0f, 10.0f / 256.0f, 40.0f / 128.0f, 0.2f);

	bullets[0]->sprite = *bulletSprite;
	bullets[0]->type = ENTITY_BULLET_PLAYER;
	bullets[0]->yPos = -10.0f;
	bullets[0]->velocity_y = 0.00f;

	for (int i = 0; i < 13; i++) {
	
		invaderA[i]->sprite = *invaderA0;
		invaderA[i]->height = invaderA[i]->sprite.size;
		invaderA[i]->width = invaderA[i]->sprite.size;
		invaderA[i]->type = ENTITY_ENEMY;
		invaderA[i]->isActive = true;
		invaderA[i]->yPos += 2.0f;
		invaderA[i]->xPos -= 1.4f -(0.3f*i);
	
		invaderB[i]->sprite = *invaderB0;
		invaderB[i]->height = invaderB[i]->sprite.size;
		invaderB[i]->width = invaderB[i]->sprite.size;
		invaderB[i]->type = ENTITY_ENEMY;
		invaderB[i]->isActive = true;
		invaderB[i]->yPos += 1.6f;
		invaderB[i]->xPos -= 1.4f - (0.3f*i);

		invaderC[i]->sprite = *invaderC0;
		invaderC[i]->height = invaderC[i]->sprite.size;
		invaderC[i]->width = invaderC[i]->sprite.size;
		invaderC[i]->type = ENTITY_ENEMY;
		invaderC[i]->isActive = true;
		invaderC[i]->yPos += 1.2f;
		invaderC[i]->xPos -= 1.4f - (0.3f*i);

		bullets[i+1]->sprite = *bulletSprite;
		bullets[i]->height = bullets[i]->sprite.size;
		bullets[i]->width = bullets[i]->sprite.size;
		bullets[i+1]->type = ENTITY_BULLET;
		bullets[i+1]->yPos = -10.0f;
	}
	
	
}


gameLevel::~gameLevel()
{
	delete player;


}

void gameLevel::Render() {
	
	Matrix modelMatrix;

	modelMatrix.identity();
	modelMatrix.Translate(-3.7f, 3.8, 0);
	programLevel->setModelMatrix(modelMatrix);

	DrawText(comicFont, "SCORE<1> HI-SCORE SCORE<2>", 0.30f, 0.001f);
	modelMatrix.Translate(0.0f, -0.5f, 0);
	programLevel->setModelMatrix(modelMatrix);
	DrawText(comicFont, "  0000    0000      0000  ", 0.30f, 0.001f);


	player->render(programLevel);
	for (int i = 0; i < 13; i++) {

		invaderA[i]->render(programLevel);
		invaderB[i]->render(programLevel);
		invaderC[i]->render(programLevel);

	}

	

	modelMatrix.identity();
	modelMatrix.Translate(-2, 2, 0);

	programLevel->setModelMatrix(modelMatrix);
	
	bullets[0]->render(programLevel);

}

void gameLevel::Update(float elapsed) {
	player->update(elapsed);
	bullets[0]->update(elapsed);

	for each (Entity *ents in bullets)
	{
		
		if (ents->isActive) {
			
			//std::cout << "checking bullets" << std::endl;
			for each (Entity *alien in invaderA) { if (alien->isActive) { alien->collideWith(ents); } }
			for each (Entity *alien in invaderB) { if (alien->isActive) { alien->collideWith(ents); } }
			for each (Entity *alien in invaderC) { if (alien->isActive) { alien->collideWith(ents); } }
		}
	}
	
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
