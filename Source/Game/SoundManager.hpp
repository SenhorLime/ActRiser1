#pragma once

#include "ResourceLoader.hpp"

class SoundManager {
public:
  sf::Sound sound;
  static SoundManager *instance;
  ResourceLoader *GetResources = ResourceLoader::resourceLoader();

public:
  SoundManager();

  virtual ~SoundManager();

  static SoundManager *SoundPlayer();

  void PlayMusic(std::string name);

  void PlaySoundEffect(std::string name);
};
