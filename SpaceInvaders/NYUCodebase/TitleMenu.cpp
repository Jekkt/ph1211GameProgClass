#include "TitleMenu.h"


TitleMenu::TitleMenu()
{
	//programMenu = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
}

TitleMenu::TitleMenu(ShaderProgram *program)
{
	programMenu = program;
}


TitleMenu::~TitleMenu()
{
}


void TitleMenu::Render() {
	Matrix modelMatrix;

	modelMatrix.identity();
	modelMatrix.Translate(-3.7f, 3.8, 0);
	programMenu->setModelMatrix(modelMatrix);

	DrawText(comicFont, "SCORE<1> HI-SCORE SCORE<2>", 0.30f, 0.00001f);
	modelMatrix.Translate(0.0f, -0.5f, 0);
	programMenu->setModelMatrix(modelMatrix);
	DrawText(comicFont, "  0000    0000      0000  ", 0.30f, 0.00001f);

	modelMatrix.identity();
	modelMatrix.Translate(-2.7f, 2, 0);
	programMenu->setModelMatrix(modelMatrix);


	DrawText(comicFont, "SPACE INVADERS", 0.4f, 0.01f);


	modelMatrix.identity();
	modelMatrix.Translate(0, 0, 0);
	programMenu->setModelMatrix(modelMatrix);
	if (alternate) {
		SheetSprite invader = SheetSprite(programMenu, alien, 62.0f / 256.0f, 0.0f / 128.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.2f);
		invader.Draw();
	}
	else {
	SheetSprite invader2 = SheetSprite(programMenu, alien, 50.0f / 256.0f, 34.0f / 128.0f, 48.0f / 256.0f, 32.0f / 128.0f, 1.2f);
	invader2.Draw();
}
	/*


	modelMatrix.identity();
	modelMatrix.Translate(2, 0, 0);


	programMenu->setModelMatrix(modelMatrix);

	SheetSprite letters = SheetSprite(programMenu, fontSpriteSheet, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f);
	letters.Draw();
	

	SheetSprite letter = SheetSprite(programMenu, fontSpriteSheet, 8.0f / (128.0f), 32.0f / 128.0f, 8.0f / 128.0f, 8.0f / 128.0f, 1.0f);
	letter.Draw();
	*/
	
}

void TitleMenu::Update(float elapsed) {
	timePassed += elapsed;

	if (timePassed > 0.5f) {
		alternate = !alternate;
		timePassed = 0.0f;
	}

}

GLuint TitleMenu::LoadTexture(const char *image_path) {

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

void TitleMenu::DrawText(int fontTexture, std::string text, float size, float spacing) {
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
	glUseProgram(programMenu->programID);

	glVertexAttribPointer(programMenu->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
	glEnableVertexAttribArray(programMenu->positionAttribute);

	glVertexAttribPointer(programMenu->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
	glEnableVertexAttribArray(programMenu->texCoordAttribute);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

	glDisableVertexAttribArray(programMenu->positionAttribute);
	glDisableVertexAttribArray(programMenu->texCoordAttribute);
}
