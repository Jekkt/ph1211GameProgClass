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

	 

	
		fps += elapsed;

		

		if (collidedBottom) {
			velocity_y = 0;
			isOnGround = true;
		}


		if (isOnGround) {
			gravity = 0.0f;
		}


	//velocity_x -= velocity_x * 0.1f;
	if (type == ENTITY_PLAYER) {

		velocity_x += acceleration_x*elapsed;
		velocity_y += (acceleration_y + gravity)*elapsed;
		
		if (velocity_x > 2.0f) {
			velocity_x = 2.0f;
		}
		else if (velocity_x < -2.0f) {
			velocity_x = -2.0f;
		}

		

		if (collidedLeft && velocity_x < 0) { velocity_x = 0; collidedLeft = false; }

		if (collidedRight && velocity_x > 0) { velocity_x = 0; collidedRight = false; }
	
		xPos += velocity_x * elapsed * 4;
		yPos += velocity_y *elapsed * 4;

		if (fps > 0.016f) { fps = 0; collidedBottom = false; }

		if (tillFall-width > xPos || tillFall+width < xPos && tillFall != 0) {
			isOnGround = false;
			std::cout << "left last block" << std::endl;
			tillFall = 0;
		}

	}

	top = yPos + height / 2;
	bot = yPos - height / 2;
	left = xPos - width / 2;
	right = xPos + width / 2;
	


}

/*void Entity::setSprite(SheetSprite spriteSheet) {
	sprite = spriteSheet;
}*/

void Entity::render(ShaderProgram *program){

	programEnt = program;

	Matrix modelMatrix;

	modelMatrix.identity();
	modelMatrix.Translate(xPos, yPos, 0);
	programEnt->setModelMatrix(modelMatrix);

	sprite.Draw(programEnt);

}

bool Entity::collideWith(Entity *ent) {

	float gridSize = 1.0f;

	//std::cout << "Collision Check." << std::endl;

	/* multiply vector with inverse of the entity's transformation matrix
		
	*/

	float pointX = xPos;
	float pointY = yPos;
	float threshold = 0.030f;
	float penetration = fabs(xPos - ent->xPos - width / 2 - ent->width / 2);

	

	if (type == ENTITY_PLAYER && ent->type == ENTITY_TILES) {

		//std::cout << ent->width<< std::endl;

		

		if (right - threshold*2 > ent->xPos - ent->width/2 && left + threshold*2 < ent->xPos + ent->width/2 ) {
			//std::cout << "player hit bottom." << std::endl;
			if (yPos <= ent->yPos + ent->height) {
				std::cout << "player hit bottom." << std::endl;
				std::cout << "Tile yPos" << ent->yPos << "Tile xPos" << ent->xPos << std::endl;
				std::cout << "Player yPos" << yPos << "Player xPos" << xPos << std::endl;
				collidedBottom = true;
				//yPos = ent->yPos + ent->height + threshold/2;
				penetration = fabs(yPos - ent->yPos - height / 2 - ent->height / 2);
				yPos = yPos + penetration + threshold;
				tillFall = xPos;
			}
		}

		if (yPos > ent->yPos - ent->height - threshold && yPos < ent->yPos + ent->height) {
			if (left <= ent->xPos + ent->width - threshold && left >= ent->xPos) {
				std::cout << "player hit left." << std::endl;
				std::cout << "Tile yPos" << ent->yPos << "Tile xPos" << ent->xPos << std::endl;
				std::cout << "Player yPos" << yPos << "Player xPos" << xPos << std::endl;
				collidedLeft = true;
				xPos = ent->xPos + ent->width + threshold;
			}

			if (right >= ent->xPos - ent->width + threshold && right <= ent->xPos) {
				std::cout << "player hit right." << std::endl;
				std::cout << "Tile yPos" << ent->yPos << "Tile xPos" << ent->xPos << std::endl;
				std::cout << "Player yPos" << yPos << "Player xPos" << xPos << std::endl;
				collidedRight = true;
				xPos = ent->xPos - ent->width - threshold;
			}
		}

		/*
		if (xPos - width / 2 < ent->xPos + ent->width) {
			std::cout << "player hit left." << std::endl;
			collidedLeft = true;
		}

		if (xPos + width / 2 > ent->xPos - ent->width) {
			std::cout << "player hit right." << std::endl;
			collidedRight = true;
		}
		*/

	}

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
