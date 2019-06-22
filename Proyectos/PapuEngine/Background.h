#pragma once
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>
using namespace std;

class Background
{
private:
	string texture;
	ColorRGBA color;
	int textureID;
	float width;
	float height;
public:
	Background(string _texture, float _width, float _height);
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
	~Background();
};

