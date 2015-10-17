#include "SheetSprite.h"

void SheetSprite::Draw() {
	

	GLfloat texCoord[] = {
		u, v + height,
		u + width, v,
		u, v,
		u + width, v,
		u, v + height,
		u + width, v + height
	};

	float aspect = width / height;
	float vertices[] = {
		-0.5f* size * aspect, -0.5f * size,
		0.5f* size * aspect, 0.5f * size,
		-0.5f* size * aspect, 0.5f * size,
		0.5f* size * aspect, 0.5f * size,
		-0.5f* size * aspect, -0.5f * size,
		0.5f* size * aspect, -0.5f * size};

	//draw arrays

	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoord);
	glEnableVertexAttribArray(program->texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);

}

SheetSprite::SheetSprite() {
	textureID = 0;
	u = 0;
	v = 0;
	width = 1;
	height = 1;
	size = 1;
	program = 0;
}

SheetSprite::~SheetSprite() {
}

SheetSprite::SheetSprite(ShaderProgram *prog) {
	program = prog;
}

SheetSprite::SheetSprite(ShaderProgram *prog, unsigned int texID, float uP, float vP, float widthP, float heightP, float sizeP) {
	textureID = texID;
	u = uP;
	v = vP;
	width = widthP;
	height = heightP;
	size = sizeP;
	program = prog;
}