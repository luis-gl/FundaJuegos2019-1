#include "Game.h"
#include "IGameScreen.h"
#include "ScreenList.h"
#include "PapuEngine.h"

Game::Game()
{
	screenList = std::make_unique<ScreenList>(this);
}

bool Game::init() {
	Papu::init();
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	initSystems();
	onInit();
	addScreen();
	currentScreen = screenList->getCurrent();
	currentScreen->onEntry();
	currentScreen->setRunning();
	return true;
}

void Game::draw()
{
	glViewport(0, 0, window.getScreenWidth(), window.getScreenHeight());
	if (currentScreen && currentScreen->getState() == ScreenState::RUNNING) {
		currentScreen->draw();
	}
}

bool Game::initSystems() {
	window.create("Holi", 760, 500, 0);
	return true;
}

void Game::onSDLEvent(SDL_Event& event) {

}

void Game::run() {
	if (!init())return;
	isRunning = true;
	while (isRunning) {
		inputManager.update();
		update();
		draw();
		window.swapBuffer();
	}
}

void Game::update() {
	if (currentScreen) {
		switch (currentScreen->getState())
		{
		case ScreenState::RUNNING:
			currentScreen->update();
			break;
		case ScreenState::CHANGE_NEXT:
			currentScreen->onExit();
			currentScreen = screenList->moveNext();
			if (currentScreen) {
				currentScreen->setRunning();
				currentScreen->onEntry();
			}
			break;
		case ScreenState::CHANGE_PREVIOUS:
			currentScreen->onExit();
			currentScreen = screenList->movePrevious();
			if (currentScreen) {
				currentScreen->setRunning();
				currentScreen->onEntry();
			}
			break;
		case ScreenState::EXIT_APPLICATION:
			exit();
			break;
		default:
			break;
		}
	}
}

Game::~Game()
{	
}
