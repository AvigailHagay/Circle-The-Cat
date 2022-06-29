#pragma once
#include "FileManager.h"
#include <iostream>

//--------------------------------------------------
//constructor

FileManager::FileManager()
{
	//loads from all the files:
	loadFromFileIcons();
	loadAudio();
	loadBackgrounds();
}
//--------------------------------------------------
//return unic pointer to the object

FileManager& FileManager::p2FileManager()
{
	static FileManager m_instance;
	return m_instance;
}
//--------------------------------------------------
// load all the object images

void FileManager::loadFromFileIcons()
{
	m_icons[HEXAGON].loadFromFile("hexagon.png");
	m_icons[CAT].loadFromFile("Cat.png");
	m_icons[EXIT].loadFromFile("exit.png");
	m_icons[RESET].loadFromFile("reset.png");
	m_icons[UNDO].loadFromFile("undo.png");

	this->m_font.loadFromFile("EvilEmpire-4BBVK.ttf");
}
//--------------------------------------------------
// load all the audio

void FileManager::loadAudio()
{
	m_audio[S_OPENING].loadFromFile("opening.ogg");
	m_audio[S_WIN].loadFromFile("win.ogg");
	m_audio[S_LOSS].loadFromFile("lost.ogg");
	m_audio[S_CLICK].loadFromFile("clickSound.ogg");
	m_audio[S_RESET].loadFromFile("reset.ogg"); 
	m_audio[S_UNDO].loadFromFile("undo.ogg");
}
//--------------------------------------------------

void FileManager::loadBackgrounds()
{
	m_backgrounds[OPENING].loadFromFile("opening.png");
	m_backgrounds[WON].loadFromFile("won.png");
	m_backgrounds[LOSS].loadFromFile("loss.png"); 
	m_backgrounds[NEXT].loadFromFile("nextLevel.png");
}
//--------------------------------------------

const sf::SoundBuffer* FileManager::getSound(sounds sound)const
{
	return &this->m_audio[(int)sound];
}
//--------------------------------------------------

const sf::Texture* FileManager::getBackGround(backgroundsType place)const
{
	return &this->m_backgrounds[place];
}
//--------------------------------------------------

const sf::Texture* FileManager::getIconTexture(icons place)const
{
	return &this->m_icons[place];
}
//--------------------------------------------------

const sf::Font* FileManager::getFont()const
{
	return &this->m_font;
}