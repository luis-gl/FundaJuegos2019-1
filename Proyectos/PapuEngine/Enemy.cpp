#include "Enemy.h"


Enemy::Enemy(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	float _screenWidth,
	float _screenHeight)
	:Agent(agent_width, agent_height, position, texture)
{
	screenWidht = _screenWidth;
	screenHeight = _screenHeight;
}

void Enemy::update()
{
	_position.y -= 6.0f;
}


std::string Enemy::getTexture()
{
	return _texturePath;
}

Enemy::~Enemy()
{
}
