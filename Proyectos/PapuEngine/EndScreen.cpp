#include "EndScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

EndScreen::EndScreen(Window * window):
	_window(window)
{
	_screenIndex = SCREEN_INDEX_OVER;
}

void EndScreen::build()
{
}

void EndScreen::destroy()
{
	delete background;
	delete button;
	delete _spriteFont;
	delete audioPlayer;
}

void EndScreen::onExit()
{
}

void EndScreen::onEntry()
{
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	initGUI();
}

void EndScreen::initGUI()
{
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 32);
	background = new Background("Textures/gameover.png", _window->getScreenWidth(), _window->getScreenHeight());
	button = new Button("Textures/menu_button.png",
		glm::vec2(_window->getScreenWidth()/2.0f, _window->getScreenHeight()*0.25f),
		190, 50);
	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/gameover.ogg");
	audioPlayer->playBackgroundSong();
}

void EndScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	char buffer[256];
	_spriteBatch.begin();
	background->draw(_spriteBatch);
	button->draw(_spriteBatch);
	sprintf(buffer, "Back to Menu");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(button->getPosition().x + button->getWidth()/2.0f, button->getPosition().y + button->getHeight()/2.0f), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255), Justification::MIDDLE);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void EndScreen::update()
{
	_camera2D.update();
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (
			!button->getClicked() &&
			button->click(_game->_inputManager.getMouseCoords(),
				glm::vec2(_window->getScreenWidth(), _window->getScreenHeight()))
			) {
			button->setClicked(true);
			std::cout << "clik" << std::endl;
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
	checkInput();
}

void EndScreen::initSystem()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

int EndScreen::getNextScreen() const
{
	return SCREEN_INDEX_MENU;
}

int EndScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void EndScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

EndScreen::~EndScreen()
{
}