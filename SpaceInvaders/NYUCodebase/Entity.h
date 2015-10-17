#pragma once
#include "ShaderProgram.h"
#include "SheetSprite.h"
#include "Matrix.h"

enum EntityType {ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET, ENTITY_BULLET_PLAYER};

class Entity {
public:

	Entity();
	Entity(ShaderProgram *progEnt);

	~Entity();

	Entity(const Entity &cSource);
	const Entity &Entity::operator = (const Entity &cSource);

	void update(float elapsed);
//	void setSprite(SheetSprite sprite);
	void render(ShaderProgram *program);
	bool collideWith(Entity *ent);

	EntityType type;

	ShaderProgram *programEnt;

	bool isStatic;
	bool isVisible;
	bool isActive;
	bool isShot;
	SheetSprite sprite;

	float startX;
	float startY;

	float xPos;
	float yPos;
	float rotZ;

	float width;
	float height;

	float velocity_x;
	float velocity_y;

	float acceleration_x;
	float acceleration_y;

	private:

		

};