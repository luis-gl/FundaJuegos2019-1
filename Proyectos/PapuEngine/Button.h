#pragma once
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>


using namespace std;

class Button
{
private:
	string texture;
	ColorRGBA color;
	int textureID;
	bool clicked;
	glm::vec2 position;
	float width;
	float height;
public:
	void setClicked(bool _clicked) {
		clicked = _clicked;
	}
	bool getClicked()const {
		return clicked;
	}
	Button(string _texture, glm::vec2 _position, float _width, float _height);
	void draw(SpriteBatch& spriteBatch);
	void setColor(ColorRGBA _color);
	ColorRGBA getColor() const {
		return color;
	}
	float getWidth() {
		return width;
	}
	float getHeight() {
		return height;
	}
	bool click(glm::vec2 _position, glm::vec2 windowSize);

	glm::vec2 getPosition()
	{
		return position;
	}
	~Button();
};

