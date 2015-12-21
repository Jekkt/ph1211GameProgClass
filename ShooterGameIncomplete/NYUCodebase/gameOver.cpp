#include "gameOver.h"



gameOver::gameOver()
{
}

gameOver::gameOver(ShaderProgram *program)
{
	programOver = program;
}

gameOver::~gameOver()
{
}


void gameOver::Render() {
	Matrix modelMatrix;

	modelMatrix.identity();
	modelMatrix.Translate(-2.5f, 0, 0);

	programOver->setModelMatrix(modelMatrix);

	DrawText(comicFont, "GAME OVER", 0.5f, 0.1f);
}

void gameOver::Update(float elapsed) {

}

GLuint gameOver::LoadTexture(const char *image_path) {

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

void gameOver::DrawText(int fontTexture, std::string text, float size, float spacing) {
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
	glUseProgram(programOver->programID);

	glVertexAttribPointer(programOver->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
	glEnableVertexAttribArray(programOver->positionAttribute);

	glVertexAttribPointer(programOver->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
	glEnableVertexAttribArray(programOver->texCoordAttribute);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

	glDisableVertexAttribArray(programOver->positionAttribute);
	glDisableVertexAttribArray(programOver->texCoordAttribute);
}