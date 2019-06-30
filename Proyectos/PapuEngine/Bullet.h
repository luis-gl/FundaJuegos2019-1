#pragma once
#include "Agent.h"

class Bullet : public Agent
{
private:
	float screenWidth;
	float screenHeight;
public:
	Bullet(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		float _screenWidth,
		float _screenHeight);
	void update();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}
	std::string getTexture();
	~Bullet();
};
