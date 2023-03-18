#pragma once

#include "Entity.h"

enum class BrickColour {BLUE = 0, GREEN, ORANGE, PURPLE, RED, YELLOW};

//externed sprites
extern Sprite *blueBrickSprite;
extern Sprite *greenBrickSprite;
extern Sprite *orangeBrickSprite;
extern Sprite *purpleBrickSprite;
extern Sprite *redBrickSprite;
extern Sprite *yellowBrickSprite;

class BrickEntity : public Entity
{
public:
	BrickColour colour;
	BrickEntity()
	{
		typeID = ENTITYBRICK;
		colour = BrickColour::BLUE;
	}
	bool HandleCollision();
};

void LoadMap(std::string fileName, std::vector<BrickEntity*>& brickEntityList);

BrickEntity * MakeBrick(BrickColour type, float xpos, float ypos);