#include "Audio.h"
#include <iostream>
#include "pch.h"

sf::SoundBuffer Audio::buffer;
sf::Music Audio::music;
sf::Sound Audio::sound;

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::Initialize()
{
	std::cout << "Audio Engine Started" << "\n";
}


void Audio::PlayMusic(std::string filename)
{
	if (!music.openFromFile("../Assets/" + filename))
	{
		printf("AUDIO ERROR\n");
		return;
	}
	music.setVolume(50.0f);
	music.play();
}

void Audio::StopMusic()
{
	music.stop();
}

void Audio::PlaySfx(std::string filename)
{
	if (!buffer.loadFromFile("../Assets/" + filename))
	{
		printf("loading SFX Failed\n");
		return;
	}

	sound.setBuffer(buffer);
	sound.play();

}