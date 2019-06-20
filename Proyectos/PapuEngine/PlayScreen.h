#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include "Gamer.h"
#include "Enemy.h"
#include <vector>
#include <random>
#include <ctime>

using namespace std;

class PlayScreen: public IGameScreen
{
private:
	GLS_Program _program;
	Gamer* player;
	Camera2D _camera2D;
	Window* _window = nullptr;
	SpriteBatch _spriteBatch;
	SpriteBatch _hudBach;
	Camera2D _hudCamera;
	vector<Enemy*> enemies;
	std::mt19937 randomEngine;
	std::uniform_int_distribution<int>prob;
	std::uniform_int_distribution<int>ranPosition;
	Enemy* toDelete;
	int probability;
	void drawHUD();
public:
	PlayScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	~PlayScreen();
};

