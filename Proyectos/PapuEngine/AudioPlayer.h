#pragma once
#include <irrKlang/irrKlang.h>
#include <string>
#include <vector>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;

class AudioPlayer
{
	ISoundEngine* audioPlayer;
	std::vector<ISound*> sounds;
public:
	AudioPlayer();
	void AddAndPlay(const char* _musicPath, bool _looped);
	void pausePlayBackgroundSong();
	void pausePlaySong(int pos);
	void pauseAllSongs();
	void continueAllSongs();
	~AudioPlayer();
};

