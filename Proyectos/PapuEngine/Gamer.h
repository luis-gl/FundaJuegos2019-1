#pragma once
#include "Agent.h"
#include "InputManager.h"
#include "AudioPlayer.h"
#include <vector>

class Gamer : public Agent
{
private:
	InputManager* inputManager;
	float _screenWidth;
	float _screenHeight;
public:
	Gamer(float agent_width,
			float agent_height,
		glm::vec2 position,
		std::string texture);
	Gamer(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* _inputManager,
		float screenWidht,
		float screenHeight);
	void update();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}
	std::string getTexture();
	~Gamer();
};

