#pragma once
/*
 * animation.hpp
 *
 *  Created on: 1 de out. de 2023
 *      Author: arsrc
 */

//#ifndef ANIMATION_HPP_
//#define ANIMATION_HPP_

#include <iostream>
#include <cassert>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

/**Classe que define os sprites que comp�e
 * uma anima��o.
 */
class Animation {
public:
	Animation(sf::Texture *texture = nullptr);
	~Animation();

	/**Define a textura a ser utilizada na anima��o. */
	void setTexture(sf::Texture *texture);
	sf::Texture* getTexture() const;

	/**Adiciona um �nico frame a anima��o
	 * @argument  &rect retangulo que representa o sprite
	 * dentro da textura.
	 * Permite coletar sprites em texturas com disposi��o
	 * das imagens n�o uniforme.
	 */
	Animation& addFrame(const sf::IntRect &rect);
	/**Adiciona uma linha de sprites a anima��o
	 * Esses frames est�o dispostos linearmente na textura.
	 * @argument  number_x - qtd de sprites em uma linha da textura
	 * @argument  number_y - qtd de sprites em uma coluna da textura
	 * @argument  line	   - qual linha da da textura ser� inserida.
	 *
	 * Esse m�todo exige que a textura tenha suas
	 */
	Animation& addFramesLine(int number_x, int number_y, int line);
	/**Adiciona uma coluna de sprites a anima��o
	 * Esses frames est�o dispostos horizontalmente na textura.
	 * @arg  number_x - qtd de sprites em uma linha da textura
	 * @arg  number_y - qtd de sprites em uma coluna da textura
	 * @arg  line	   - qual linha da da textura ser� inserida.
	 *
	 * Esse m�todo exige que a textura tenha suas
	 */
	Animation& addFramesColumn(int number_x, int number_y, int column);

	Animation& addFrames(const sf::IntRect &rect, int linhas, int colunas);
	size_t size() const;

	/**Retorna a rect do sprite na posi��o index */
	sf::IntRect& getRect(size_t index);

private:
	friend class AnimatedSprite;
	std::vector<sf::IntRect> _frames;
	sf::Texture *_texture;
};

/**
 * @class AnimatedSprite
 * @brief Utilizada no local do Sprite da aplica��o
 * 		  Os sprites s�o substituidos pela classe Animation
 * 		  que recebe a textura e marca os sprites.
 * 		  Essa classe controla a anima��o dos sprites em
 * 		  cada objeto da classe Animation.
 */
class AnimatedSprite: public sf::Sprite {
//class AnimatedSprite: public sf::Drawable, public sf::Transformable {
public:
	AnimatedSprite(const AnimatedSprite&) = default;
	AnimatedSprite& operator=(const AnimatedSprite&) = default;
	AnimatedSprite(AnimatedSprite&&) = default;
	AnimatedSprite& operator=(AnimatedSprite&&) = default;

	enum Status {
		Stopped, Paused, Playing
	};

	/**
	 * @fn  AnimatedSprite(Animation*=nullptr, Status=Playing, const sf::Time&=sf::seconds(0.15), bool=true, int=0)
	 * @param animation = J� recebe uma primeira anima��o. Default = nullptr.
	 * @param status	= Situa��o atual da anima��o {Stopped, Paused, Playing }
	 * @param deltaTime = Tempo entre os sprites. Default = sf::seconds(0.15)
	 * @param loop = Se a anima��o ser� repetida. Default = true.
	 * @param repeat = Se n�o est� em loop quantas vezes deve repetir. Default = 0.
	 * @brief
	 * Pode ser inicializada sem nada somente com os parametros padr�o e depois
	 * modificados com os get and sets da classe.
	 *
	 * As demais fun��es s�o auto explicativas.
	 */
	AnimatedSprite(Animation *animation = nullptr, Status status = Playing,
			const sf::Time &deltaTime = sf::seconds(0.15), bool loop = true,
			int repeat = 0);

	void setAnimation(Animation *animation);
	Animation* getAnimation() const;

	void setFrameTime(sf::Time deltaTime);
	sf::Time getFrameTime() const;

	void setLoop(bool loop);
	bool getLoop() const;
	void setRepeat(int nb);
	int getRepeat() const;

	void play();
	void pause();
	void stop();
	Status getStatus() const;

	void setFrame(size_t index);
	void setColor(const sf::Color &color);
	void update(const sf::Time &deltaTime);
	void draw(sf::RenderTarget &target) const;
private:
	Animation *_animation;
	sf::Time _delta;
	sf::Time _elapsed;
	bool _loop;
	int _repeat;
	Status _status;
	size_t _currentFrame;
	sf::Vertex _vertices[4];

	void setFrame(size_t index, bool resetTime);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
			override;

};

//#endif /* ANIMATION_HPP_ */
