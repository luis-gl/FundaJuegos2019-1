#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include <random>
#include <ctime>


PlayScreen::PlayScreen(Window* window):_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	
	player = new Gamer(106, 79,
		glm::vec2(327, 20), "Textures/Player.png", 
		&_game->_inputManager,
		_window->getScreenWidth(),
		_window->getScreenHeight());
	initGUI();
	
}



void PlayScreen::update() {
	_camera2D.update();
	player->update();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
		if (enemies[i]->getPosition().y >= _window->getScreenHeight())
		{
			enemies.erase(enemies.begin() + i);
		}
	}
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>prob(0, 100);
	std::uniform_int_distribution<int>ranPosition(0, _window->getScreenWidth());
	int probability = prob(randomEngine);
	if (probability >= 20 && probability < 40)
	{
		Enemy* enemy = new Enemy(64, 64,
			glm::vec2(ranPosition(randomEngine), 300.0f),
			"Textures/Nave.png",
			_window->getScreenWidth(),
			_window->getScreenHeight());
		enemies.push_back(enemy);
	}
	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();;
	player->draw(_spriteBatch);
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(_spriteBatch);
	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();

	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
