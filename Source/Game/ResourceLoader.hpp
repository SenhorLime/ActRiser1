/*
 * ResourceLoader.h
 *
 *  Created on: 3 de out. de 2023
 *      Author: arsrc
 */

#ifndef SOURCE_GAME_RESOURCELOADER_HPP_
#define SOURCE_GAME_RESOURCELOADER_HPP_

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>

class ResourceLoader {
public:
  static ResourceLoader *instance;

  std::map<std::string, sf::Texture> textureMap;
  std::map<std::string, sf::SoundBuffer *> soundMap;
  std::map<std::string, sf::Music *> musicMap;

  sf::Sound soundEffects;
  sf::Music musics;
  sf::Texture textura;

  ResourceLoader();

  static ResourceLoader *resourceLoader();

  virtual ~ResourceLoader();

  sf::Music *getMusics(std::string nome);

  void addMusics(std::string nome, std::string path);

  sf::SoundBuffer *getSoundEfects(std::string nome);

  void addSoundEfects(std::string nome, std::string path);

  sf::Texture *getTextura(std::string nome);

  void addTextura(std::string nome, std::string path);

  void addTextura(std::string nome, sf::Texture &texture);

private:
};

#endif /* SOURCE_GAME_RESOURCELOADER_HPP_ */
