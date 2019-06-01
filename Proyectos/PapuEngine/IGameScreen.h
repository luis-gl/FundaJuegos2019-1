#pragma once

enum class ScreenState {
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};

class Game;

class IGameScreen
{
protected:
	ScreenState currentState = ScreenState::NONE;
	Game* game = nullptr;
public:
	int screenIndex = 1;
	virtual void build() = 0;
	virtual void destroy() = 0;
	virtual void onExit() = 0;
	virtual void onEntry() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual int getNextScreen() const = 0;
	virtual int getPreviousScreen() const = 0;
	ScreenState getState()const {
		return currentState;
	}
	void setRunning() {
		currentState = ScreenState::RUNNING;
	}
	void setParent(Game* _game) {
		game = _game;
	}
	IGameScreen();
	virtual ~IGameScreen();
};

