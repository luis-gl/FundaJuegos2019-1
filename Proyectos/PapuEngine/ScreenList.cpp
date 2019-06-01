#include "ScreenList.h"
#include "IGameScreen.h"



ScreenList::ScreenList(Game * _game) : game(_game)
{
}

ScreenList::~ScreenList()
{
	destroy();
}

IGameScreen * ScreenList::moveNext()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getNextScreen() != -1) {
		currentIndex = currentScreen->getNextScreen();
	}
	return getCurrent();
}

IGameScreen * ScreenList::movePrevious()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getNextScreen() != -1) {
		currentIndex = currentScreen->getPreviousScreen();
	}
	return getCurrent();
}

void ScreenList::setScreen(int nextScreen)
{
	currentIndex = nextScreen;
}

void ScreenList::addScreen(IGameScreen* newScreen)
{
	newScreen->screenIndex = screens.size();
	screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParent(game);
}

void ScreenList::destroy()
{
	for (size_t i = 0; i < screens.size(); i++) {
		screens[i]->destroy();
	}
	currentIndex = -1;
	screens.resize(0);
}

IGameScreen * ScreenList::getCurrent()
{
	if (currentIndex == -1) {
		return nullptr;
	}
	return screens[currentIndex];
}
