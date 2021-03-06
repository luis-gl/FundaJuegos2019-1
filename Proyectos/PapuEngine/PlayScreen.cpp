#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"


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
	spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	background = new Background("Textures/game.png", _window->getScreenWidth(), _window->getScreenHeight());
	audioPlayer = new AudioPlayer();
	audioPlayer->addToTrack("Audio/game.ogg");		//0 para el backgroundMusic
	audioPlayer->addToTrack("Audio/loseLife.ogg");	//1 para perder vida
	audioPlayer->addToTrack("Audio/dead.ogg");		//2 para morir
	audioPlayer->playBackgroundSong();
	playerLifes = 3;
	score = 0;
	countToDie = 0;
	startCTD = false;
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
	delete background;
	delete audioPlayer;
	delete spriteFont;
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
	randomEngine = mt19937(time(nullptr));
	prob = uniform_int_distribution<int>(0, 100);
	ranPosition = uniform_int_distribution<int>(0, _window->getScreenWidth());
	countToSpawn = 0;
	initGUI();
}



void PlayScreen::update() {
	_camera2D.update();
	player->update();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
		if (enemies[i]->getPosition().y <= 0.0f)
		{
			Enemy* toDelete = nullptr;
			toDelete = enemies[i];
			enemies.erase(enemies.begin() + i);
			delete toDelete;
			score += 10;
		}
		else if (enemies[i]->collideWithAgent(player))
		{
			if (playerLifes > 0) {
				audioPlayer->playSong(1);
				playerLifes--;
			}
			else {
				audioPlayer->playSong(2);
				startCTD = true;
			}
			Enemy* toDelete = nullptr;
			toDelete = enemies[i];
			enemies.erase(enemies.begin() + i);
			delete toDelete;
		}
	}
	if (startCTD) {
		countToDie++;
		if (countToDie > 30) {
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
	countToSpawn++;
	if (countToSpawn == 10)
	{
		Enemy* enemy = new Enemy(80, 80,
			glm::vec2(ranPosition(randomEngine), _window->getScreenHeight() - 80),
			"Textures/Nave.png",
			_window->getScreenWidth(),
			_window->getScreenHeight());
		enemies.push_back(enemy);
		countToSpawn = 0;
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
	_spriteBatch.begin();
	background->draw(_spriteBatch);
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
	sprintf(buffer, "Lifes: %d", playerLifes);
	spriteFont->draw(_hudBach, buffer,
		glm::vec2(_window->getScreenWidth()*0.15, _window->getScreenHeight()*0.05), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255), Justification::MIDDLE);
	sprintf(buffer, "Score: %d", score);
	spriteFont->draw(_hudBach, buffer,
		glm::vec2(_window->getScreenWidth()*0.30, _window->getScreenHeight()*0.05), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255), Justification::MIDDLE);
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
