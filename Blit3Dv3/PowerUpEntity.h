#pragma once

#include "Entity.h"

enum class PowerUpType { MULTIBALL , SPEEDBALL };

class PowerUpEntity : public Entity
{
private:	
	int currentFrameNum;
	float timeBetweenFrames;
	float frameTimer;
public:
	PowerUpType powerUpType = PowerUpType::MULTIBALL;
	std::vector<Sprite *> spriteList;
	PowerUpEntity();
	void Update(float seconds);
};

PowerUpEntity * MakePowerUp(PowerUpType type, float xpos, float ypos);