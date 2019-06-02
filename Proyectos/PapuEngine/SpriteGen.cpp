#include "SpriteGen.h"
#include "ResourceManager.h"


void SpriteGen::init(glm::vec2 _position, char _type)
{
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	type = _type;
	position = _position;
}

void SpriteGen::draw(SpriteBatch& spritebatch)
{
	static int textureID;
	switch (type)
	{
	case 'A':
		textureID = ResourceManager::getTexture("Textures/megaman.png").id;
		break;
	case 'B':
		textureID = ResourceManager::getTexture("Textures/mario.png").id;
		break;
	case 'C':
		textureID = ResourceManager::getTexture("Textures/shadow.png").id;
		break;
	case 'D':
		textureID = ResourceManager::getTexture("Textures/arthas.png").id;
		break;
	default:
		textureID = ResourceManager::getTexture("Textures/mario.png").id;
		break;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, SPRT_WIDTH, SPRT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

SpriteGen::SpriteGen()
{
}


SpriteGen::~SpriteGen()
{
}
