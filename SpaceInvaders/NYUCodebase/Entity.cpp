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
	//float gravity = -4.0f;

	//velocity_x = acceleration_x * elapsed;
	if (-3.0f < yPos + velocity_y*elapsed && yPos + velocity_y*elapsed < 3.0f) {
		yPos += velocity_y * elapsed;
	}
	else if (type = ENTITY_BULLET_PLAYER) {
		yPos = -10;
		isShot = false;
		isActive = false;
	}


	if (-3.0f < xPos + velocity_x*elapsed && xPos + velocity_x*elapsed < 3.0f){
		xPos += velocity_x * elapsed;
	}
	


}

/*void Entity::setSprite(SheetSprite spriteSheet) {
	sprite = spriteSheet;
}*/

void Entity::render(ShaderProgram *program){

	//programEnt = program;

	Matrix modelMatrix;

	modelMatrix.identity();
	modelMatrix.Translate(xPos, yPos, 0);
	programEnt->setModelMatrix(modelMatrix);

	sprite.Draw();

}

bool Entity::collideWith(Entity *ent) {

	//std::cout << "Collision Check." << std::endl;

	if (type == ENTITY_ENEMY && ent->type == ENTITY_BULLET_PLAYER) {
		//std::cout << "player bullet." << std::endl;

		if (ent->yPos > yPos) {

			if (xPos + width/2 > ent->xPos) {
				
				if(xPos - width/2 < ent->xPos){
					xPos = -10;
					ent->velocity_y = 0;
					ent->xPos = -10;
					isActive = false;
					ent->isActive = false;
					ent->isShot = false;
					std::cout << "Alien destroyed." << std::endl;
					return true;
				}
			}

			
		}
	}

	return false;
}
