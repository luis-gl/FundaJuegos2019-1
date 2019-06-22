#include "Button.h"
#include "ResourceManager.h";


Button::Button(std::string _texture, glm::vec2 _position, float _width, float _height)
	:texture(_texture), clicked(false)
{
	width = _width;
	height = _height;
	position = glm::vec2(_position.x - _width/2, _position.y - _height/2);
	textureID
		= ResourceManager::getTexture(texture).id;
	color.set(255, 255, 255, 255);
}

void Button::draw(SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(position.x, position.y, width, height);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Button::setColor(ColorRGBA _color) {
	color = _color;
}

bool Button::click(glm::vec2 _position, glm::vec2 windowSize)
{
	bool result = (_position.x > position.x)
		&& (_position.x < position.x + 190)
		&& (windowSize.y - _position.y > position.y)
		&& (windowSize.y - _position.y < position.y + 50);
	return result;
}

Button::~Button()
{
}
