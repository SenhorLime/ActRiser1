/*
 * ResourceLoader.cpp
 *
 *  Created on: 3 de out. de 2023
 *      Author: arsrc
 */

#include "ResourceLoader.hpp"

#include <cstddef> //For nullptr_t
#include <string>

ResourceLoader *ResourceLoader::instance = nullptr;

ResourceLoader::ResourceLoader() {

}

ResourceLoader *ResourceLoader::resourceLoader() {
    if (instance == nullptr) {
        instance = new ResourceLoader();
    }
    return instance;
}

sf::Music *ResourceLoader::getMusics(std::string nome) {
    auto it = musicMap.find(nome);
    if (it == musicMap.end()) {
        std::cerr << "N�o foi possivel abrir a textura " << nome << "."
                  << std::endl;
        return nullptr;
    }
    return ((it->second));
}

void ResourceLoader::addMusics(std::string nome, std::string path) {
    sf::Music *_music = new sf::Music();
    if (!_music->openFromFile(path)) {
        std::cerr << "N�o foi possivel adicionar a m�sica: " << nome
                  << ". Local:" << path << std::endl;
    }
    musicMap.insert({nome, _music});
}

sf::SoundBuffer *ResourceLoader::getSoundEfects(std::string nome) {
    auto it = soundMap.find(nome);
    if (it == soundMap.end()) {
        std::cerr << "N�o foi possivel abrir a textura " << nome << "."
                  << std::endl;
        return nullptr;
    }
    return ((it->second));
}

void ResourceLoader::addSoundEfects(std::string nome, std::string path) {
    sf::SoundBuffer *_soundEffect = new sf::SoundBuffer();
    if (!_soundEffect->loadFromFile(path)) {
        std::cerr << "N�o foi possivel adicionar a m�sica: " << nome
                  << ". Local:" << path << std::endl;
    }
    soundMap.insert({nome, _soundEffect});
}

sf::Texture *ResourceLoader::getTextura(std::string nome) {
    auto it = textureMap.find(nome);
    if (it == textureMap.end()) {
        std::cerr << "N�o foi possivel abrir a textura " << nome << "."
                  << std::endl;
        return nullptr;
    }

    return (&(textureMap[nome]));
}

void ResourceLoader::addTextura(std::string nome, std::string path) {
    sf::Texture _texture;
    if (!_texture.loadFromFile(path)) {
        std::cerr << "N�o foi possivel adicionar a textura: " << nome
                  << ". Local:" << path << std::endl;
    }
    addTextura(nome, _texture);
}

void ResourceLoader::addTextura(std::string nome, sf::Texture &texture) {
    textureMap.insert({nome, sf::Texture(texture)});
}


ResourceLoader::~ResourceLoader() {
    // TODO Auto-generated destructor stub
}

