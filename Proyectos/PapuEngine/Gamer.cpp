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
}

std::string Gamer::getTexture() {
	return _texturePath;
}


Gamer::~Gamer()
{
}
