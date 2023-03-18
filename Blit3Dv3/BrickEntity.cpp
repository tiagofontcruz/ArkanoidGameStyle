#include "BrickEntity.h"
#include "CollisionMask.h"

//Decide whether to change colour or die off:
//return true if this pbject should be removed
bool BrickEntity::HandleCollision()
{
	bool retval = false;
	switch(colour)
	{
	case BrickColour::BLUE:
		sprite = blueBrickSprite;
		retval = true;
		break;

	case BrickColour::GREEN:
		sprite = greenBrickSprite;
		retval = true;
		break;

	case BrickColour::ORANGE:
		sprite = orangeBrickSprite;
		retval = true;
		break;

	case BrickColour::PURPLE:
		sprite = purpleBrickSprite;
		retval = true;
		break;

	case BrickColour::RED:
		sprite = redBrickSprite;
		retval = true;
		break;

	case BrickColour::YELLOW:
		sprite = yellowBrickSprite;
		
	default: //because PURPLE wasn't handled yet, it will be handled by the default case
		retval = true;
		break;
	}
	return retval;
}

extern b2World *world;

BrickEntity * MakeBrick(BrickColour type, float xpos, float ypos)
{
	BrickEntity *brickEntity = new BrickEntity();
	brickEntity->colour = type;

	//set the sprite to draw with
	switch(type)
	{
	case BrickColour::BLUE:
		brickEntity->sprite = blueBrickSprite;
		break;

	case BrickColour::GREEN:
		brickEntity->sprite = greenBrickSprite;
		break;

	case BrickColour::ORANGE:
		brickEntity->sprite = orangeBrickSprite;
		break;

	case BrickColour::PURPLE:
		brickEntity->sprite = purpleBrickSprite;
		break;

	case BrickColour::RED:
		brickEntity->sprite = redBrickSprite;
		break;

	case BrickColour::YELLOW:
		brickEntity->sprite = yellowBrickSprite;
		break;
	}

	//make the physics body
	b2BodyDef brickBodyDef;

	//set the position of the center of the body, 
	//converting from pxel coords to physics measurements
	brickBodyDef.position.Set(xpos / PTM_RATIO, ypos / PTM_RATIO);
	brickBodyDef.type = b2_kinematicBody; //make it a kinematic body i.e. one moved by us

	//make the userdata point back to this entity
	brickBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(brickEntity);

	brickEntity->body = world->CreateBody(&brickBodyDef); //create the body and add it to the world

	// Define a box shape for our dynamic body.
	b2PolygonShape boxShape;
	//SetAsBox() takes as arguments the half-width and half-height of the box
	boxShape.SetAsBox(64.0f / (2.f*PTM_RATIO), 32.0f / (2.f*PTM_RATIO));

	b2FixtureDef brickFixtureDef;
	brickFixtureDef.shape = &boxShape;
	brickFixtureDef.density = 1.0f; //won't matter, as we made this kinematic
	brickFixtureDef.restitution = 0;
	brickFixtureDef.friction = 0.1f;

	//collison masking
	brickFixtureDef.filter.categoryBits = CMASK_BRICK;  //this is a brick
	brickFixtureDef.filter.maskBits = CMASK_BALL;		//it collides wth balls

	brickEntity->body->CreateFixture(&brickFixtureDef);
	
	return brickEntity;
}

void LoadMap(std::string fileName, std::vector<BrickEntity*>& brickEntityList)
{
	//clear the current brickList
	for (auto B : brickEntityList) delete B;
	brickEntityList.clear();

	//open file
	std::ifstream myfile;
	myfile.open(fileName);

	if (myfile.is_open())
	{
		//read in # of bricks
		int brickNum = 0;
		myfile >> brickNum;

		//read in each brick
		for (; brickNum > 0; --brickNum)
		{
			//make a brick			
			int t = 0;
			myfile >> t;
			BrickColour typeID = (BrickColour)t;
			float x, y;
			myfile >> x;
			myfile >> y;
			BrickEntity* B = MakeBrick(typeID, x, y);
			brickEntityList.push_back(B);
		}
		myfile.close();
	}
}