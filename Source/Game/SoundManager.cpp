#include "SoundManager.hpp"

SoundManager *SoundManager::instance = nullptr;

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {}

SoundManager *SoundManager::SoundPlayer() {
    if (instance == nullptr) {
        instance = new SoundManager();
    }

    return instance;
}

void SoundManager::PlayMusic(std::string name) {
    sf::Music *music = GetResources->getMusics(name);

    music->play();
    music->setVolume(75);
    music->setLoop(true);
}

void SoundManager::PlaySoundEffect(std::string name) {
    sf::SoundBuffer *soundBuffer = GetResources->getSoundEfects(name);

    sound.setBuffer(*soundBuffer);
    sound.play();
}