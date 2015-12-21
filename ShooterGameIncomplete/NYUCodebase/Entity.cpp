#include "Entity.h"


Entity::Entity()
{
	
}

Entity::Entity(ShaderProgram *progEnt)
{
	programEnt = progEnt;
	isStatic = false;
	SheetSprite *sprite = new SheetSprite(programEnt);
}

Entity::Entity(EntityType type, float xPos, float yPos, SheetSprite *sprite) {
	this->type = type;
	this->xPos = xPos;
	this->yPos = yPos;
	this->sprite = *sprite;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	collidedTop = false;
}

Entity::Entity(EntityType type, float xPos, float yPos, float zPos, SheetSprite *sprite) {
	this->type = type;
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;

	this->position.x = xPos;
	this->position.y = yPos;
	this->position.z = zPos;

	this->sprite = *sprite;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	collidedTop = false;
}

Entity::~Entity() {

}

Entity::Entity(const Entity &cSource) {

	Entity();

	operator = (cSource);
}

const Entity &Entity::operator = (const Entity &cSource) {

	return *this;
}

void Entity::update(float elapsed) {
	float gravity = -2.0f;

	if (acceleration_x > 1.0f) {
		acceleration_x = 1.0f;
	}
	else if (acceleration_x < -1.0f) {
		acceleration_x = -1.0f;
	}
	if (acceleration_z > 1.0f) {
		acceleration_z = 1.0f;
	}
	else if (acceleration_z < -1.0f) {
		acceleration_z = -1.0f;
	}


	if (!isStatic) {
		velocity_z = acceleration_z*elapsed;
		velocity_y = acceleration_y*elapsed;
		velocity_x = acceleration_x*elapsed;
		
		xPos += velocity_x;
		yPos += velocity_y;
		zPos += velocity_z;
		
		position.x += velocity_x;
		position.y += velocity_y;
		position.z += velocity_z;

		acceleration_z = acceleration_z*friction;
		acceleration_x = acceleration_x*friction;

		//Vector vector;
		//vector.addVector(getPosition(), eyeVector);

	}

}

void Entity::setEyeVector(Vector3 newEyePos) {
	eyeVector.x = newEyePos.x;
	eyeVector.y = newEyePos.y;
	eyeVector.z = newEyePos.z;
}

Vector3 Entity::getEyeVector() {
	return eyeVector;
}

void Entity::setUpVector(Vector3 newUpPos) {
	upVector.x = newUpPos.x;
	upVector.y = newUpPos.y;
	upVector.z = newUpPos.z;
}

Vector3 Entity::getUpVector() {
	return upVector;
}

void Entity::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3 Entity::getPosition() {
	return position;
}

/*void Entity::setSprite(SheetSprite spriteSheet) {
	sprite = spriteSheet;
}*/

void Entity::render(ShaderProgram *program){

	programEnt = program;

	Matrix modelMatrix;
	Matrix viewMatrix;

	modelMatrix.identity();
	viewMatrix.identity();
	programEnt->setModelMatrix(modelMatrix);

	modelMatrix.Translate(position.x, position.y, position.z);
	//modelMatrix.Yaw(rotation.z);
	//modelMatrix.Roll(rotation.x);
	//modelMatrix.Pitch(rotation.y);

	
	programEnt->setModelMatrix(modelMatrix);


	sprite.Draw(programEnt);

}

bool Entity::collideWith(Entity *ent) {

	//std::cout << "Collision Check." << std::endl;

	/* multiply vector with inverse of the entity's transformation matrix
		
	*/
	return false;
}

float lerp(float from, float to, float time) {
	float result = 0;
	
	result = (1.0 - time)*from + time*to;

	return result;
}