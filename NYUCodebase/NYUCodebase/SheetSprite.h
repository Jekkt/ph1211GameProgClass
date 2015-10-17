#pragma once
#include "ShaderProgram.h"

class SheetSprite{
public:
	SheetSprite();
	SheetSprite(ShaderProgram *program);
	SheetSprite(ShaderProgram *prog, unsigned int textureID, float u, float v, float width, float height, float size);
	~SheetSprite();

	ShaderProgram *program;

	void Draw();

	float size;
	unsigned int textureID;
	float u;
	float v;
	float width;
	float height;
	bool isStatic;

};