#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float agent_width, float agent_height, glm::vec2 position, std::string texture, float _screenWidth, float _screenHeight)
	:Agent(agent_width, agent_height, position, texture)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
}

void Bullet::update()
{
	_position.y += 10.0f;
}

std::string Bullet::getTexture()
{
	return _texturePath;
}

Bullet::~Bullet()
{
	std::cout << "bala eliminada\n";
}