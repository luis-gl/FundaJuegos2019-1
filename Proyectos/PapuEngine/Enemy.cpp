#include "Enemy.h"
#include <iostream>


Enemy::Enemy(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	float _screenWidth,
	float _screenHeight)
	:Agent(agent_width, agent_height, position, texture)
{
	_screenWidth = screenWidht;
	_screenHeight = screenHeight;
}

void Enemy::update()
{
	_position.y -= 8.0f;
	std::cout << _position.y << std::endl;
}


std::string Enemy::getTexture()
{
	return _texturePath;
}

Enemy::~Enemy()
{
	std::cout << "se elimino el enemigo" << std::endl;
}
