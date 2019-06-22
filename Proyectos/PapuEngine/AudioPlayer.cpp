#include "AudioPlayer.h"


AudioPlayer::AudioPlayer()
{
	audioPlayer = createIrrKlangDevice();
}

void AudioPlayer::AddAndPlay(const char* _musicPath, bool _looped = false)
{
	ISound* sound = audioPlayer->play2D(_musicPath, _looped, false, true, ESM_AUTO_DETECT, true);
	sounds.push_back(sound);
}

void AudioPlayer::pausePlayBackgroundSong()
{
	sounds[0]->setIsPaused(!sounds[0]->getIsPaused());
}

void AudioPlayer::pausePlaySong(int pos)
{
	sounds[pos]->setIsPaused(!sounds[pos]->getIsPaused());
}

void AudioPlayer::pauseAllSongs()
{
	if (sounds.size() > 1) {
		for (size_t i = 1; i < sounds.size(); i++) {
			sounds[i]->setIsPaused(true);
		}
	}
	
}

void AudioPlayer::continueAllSongs()
{
	if (sounds.size() > 1) {
		for (size_t i = 1; i < sounds.size(); i++) {
			sounds[i]->setIsPaused(false);
		}
	}
}

AudioPlayer::~AudioPlayer()
{
	audioPlayer->drop();
}
