#pragma once

#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../animation.hpp"
#include "../../Game/ResourceLoader.hpp"

class Character {
public:
	sf::Sprite sprite;
	bool ativo=true; // Variável para retirar objeto do jogo.
	//Para animações
	sf::Texture * _texture;
	AnimatedSprite animatedSprite;
	std::map<std::string, Animation> animacoes;



public:
	virtual void UpdateDeltaTime(float &dt);
	virtual void draw(sf::RenderTarget *target);
	virtual ~Character();
protected:
	sf::Texture * texture;
	sf::Clock animationFrameTime;
	float speed;
	float deltaTime;

protected:
	virtual void SetSprites();
	virtual void LoadTextures(std::string textureName);
	virtual void CropSprites(sf::IntRect spriteRect);
	virtual void SetScale(sf::Vector2f spriteScale);
	virtual void Move(sf::Vector2f movement);

};
