#include "Gamer.h"
#include <SDL\SDL.h>


Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture):
	Agent(agent_width,agent_height,position,texture)
{
	_screenWidth = 0.0f;
	_screenHeight = 0.0f;
}

Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* _inputmanager,
	float screenWidht,
	float screenHeight
) :Agent(agent_width, agent_height, position, texture) {
	inputManager = _inputmanager;
	_screenWidth = screenWidht;
	_screenHeight = screenHeight;
}

void Gamer::update() {
	if (inputManager->isKeyDown(SDLK_w)) {
		_position.y += 8.0f;
		if (_position.y >= _screenHeight - _agent_radius)
		{
			_position.y = 0.0f - _agent_radius;
		}
	}

	if (inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 8.0f;
		if (_position.y <= 0.0f)
		{
			_position.y = _screenHeight - _agent_radius;
		}
	}

	if (inputManager->isKeyDown(SDLK_a)) {
		_position.x -= 8.0f;
		if (_position.x <= 0.0f)
		{
			_position.x = _screenWidth - _agent_radius;
		}
	}

	if (inputManager->isKeyDown(SDLK_d)) {
		_position.x += 8.0f;
		if (_position.x >= _screenWidth - _agent_radius)
		{
			_position.x = 0.0f - _agent_radius;
		}
	}

	if (inputManager->isKeyDown(SDLK_SPACE)) {
		if (bullets.size() <= 20)
		{
			Bullet* bullet = new Bullet(30, 30, _position, "Textures/laser.png", _screenWidth, _screenHeight);
			bullets.push_back(bullet);
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->getPosition().y > _screenHeight)
		{
			Bullet* toDel = nullptr;
			toDel = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete toDel;
		}
	}
}

std::string Gamer::getTexture() {
	return _texturePath;
}

void Gamer::drawBullets(SpriteBatch& _spriteBatch)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(_spriteBatch);
	}
}


Gamer::~Gamer()
{
}
