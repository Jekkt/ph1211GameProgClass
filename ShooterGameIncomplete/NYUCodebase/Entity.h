#pragma once
#include "ShaderProgram.h"
#include "SheetSprite.h"
#include "Matrix.h"
#include "Vector3.h"

enum EntityType {ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET, ENTITY_BULLET_PLAYER, ENTITY_BACKGROUND, ENTITY_MOON, ENTITY_TILES};

class Entity {
public:

	Entity();
	Entity(ShaderProgram *progEnt);

	Entity(EntityType type, float xPos, float yPos, SheetSprite *sprite);
	Entity(EntityType type, float xPos, float yPos, float zPos, SheetSprite *sprite);

	~Entity();

	Entity(const Entity &cSource);
	const Entity &Entity::operator = (const Entity &cSource);

	void update(float elapsed);
//	void setSprite(SheetSprite sprite);
	void render(ShaderProgram *program);
	bool collideWith(Entity *ent);
	void setPosition(float x, float y, float z);
	Vector3 getPosition();
	void setEyeVector(Vector3 newEyeVec);
	Vector3 getEyeVector();

	void setUpVector(Vector3 newUpVec);
	Vector3 getUpVector();

	Matrix matrix;

	EntityType type;

	float tillFall;

	float lerp();

	float animationTime;

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
	float zPos;
	float rotZ;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 eyeVector;
	Vector3 upVector;

	Vector3 velocity;
	Vector3 acceleration;

	float width;
	float height;

	float velocity_x;
	float velocity_y;
	float velocity_z;

	float top = yPos + height / 2;
	float bot = yPos - height / 2;
	float left = xPos - width / 2;
	float right = xPos + width / 2;

	float acceleration_x;
	float acceleration_y;
	float acceleration_z;

	bool isOnGround = false;

	bool collidedTop = false;
	bool collidedBottom = false;
	bool collidedLeft = false;
	bool collidedRight = false;

	float friction = 0.90f;

	private:

		

};