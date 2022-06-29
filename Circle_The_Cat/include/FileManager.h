#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "macros.h"

class FileManager
{
public:
	~FileManager() {};
	static FileManager& p2FileManager();
	const sf::Texture* getIconTexture(icons)const;
	/*const sf::Texture* getPlayAndStopIcon(bool)const;*/
	const sf::SoundBuffer* getSound(sounds)const;
	/*const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;*/
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Font* getFont()const;

private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	void loadFromFileIcons();
	void loadAudio();/*
	void loadMusicIcon();
	void loadStopAndPlayIcon();
	void loadResetIcon();*/
	void loadBackgrounds();

	sf::Texture m_icons[NUM_OF_ICONS];
	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_restartIcon;
	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::Font m_font;
};