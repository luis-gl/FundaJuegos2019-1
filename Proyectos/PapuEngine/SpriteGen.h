#pragma once
#include <glm\glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"

const float SPRT_WIDTH = 60.0f;
const float SPRT_RADIUS = SPRT_WIDTH/2.0f;

class SpriteGen
{
private:
	glm::vec2 position;
	char type;
	Color color;
public:
	glm::vec2 getPosition() const {
		return position;
	}
	void init(glm::vec2 _position, char _type);
	void draw(SpriteBatch& spritebatch);
	SpriteGen();
	~SpriteGen();
};

