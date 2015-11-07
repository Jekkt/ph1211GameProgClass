#pragma once
#include "ShaderProgram.h"
#include "SheetSprite.h"
#include "Matrix.h"
#include "Vector.h"

enum EntityType {ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET, ENTITY_BULLET_PLAYER, ENTITY_BACKGROUND, ENTITY_MOON, ENTITY_TILES};

class Entity {
public:

	Entity();
	Entity(ShaderProgram *progEnt);

	Entity(EntityType type, float xPos, float yPos, SheetSprite *sprite);

	~Entity();

	Entity(const Entity &cSource);
	const Entity &Entity::operator = (const Entity &cSource);

	void update(float elapsed);
//	void setSprite(SheetSprite sprite);
	void render(ShaderProgram *program);
	bool collideWith(Entity *ent);

	Matrix matrix;

	EntityType type;

	float tillFall;

	ShaderProgram *programEnt;

	bool isStatic;
	bool isVisible;
	bool isActive;
	bool isShot;
	SheetSprite sprite;

	float startX;
	float startY;

	float fps = 0;

	float xPos;
	float yPos;
	float rotZ;

	float width;
	float height;

	float velocity_x;
	float velocity_y;

	float top = yPos + height / 2;
	float bot = yPos - height / 2;
	float left = xPos - width / 2;
	float right = xPos + width / 2;

	float acceleration_x;
	float acceleration_y;

	bool isOnGround = false;

	bool collidedTop = false;
	bool collidedBottom = false;
	bool collidedLeft = false;
	bool collidedRight = false;

	private:

		

};