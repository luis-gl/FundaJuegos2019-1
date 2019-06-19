#include "Gamer.h"
#include <SDL\SDL.h>


Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture):
	Agent(agent_width,agent_height,position,texture)
{

}

Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* _inputmanager
) :Agent(agent_width, agent_height, position, texture) {
	inputManager = _inputmanager;
}

void Gamer::update() {
	if (inputManager->isKeyDown(SDLK_w)) {
		_position.y += 8.0f;
	}

	if (inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 8.0f;
	}
}

std::string Gamer::getTexture() {
	return _texturePath;
}


Gamer::~Gamer()
{
}
