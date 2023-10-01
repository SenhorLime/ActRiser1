/*
 * animation.hpp
 *
 *  Created on: 1 de out. de 2023
 *      Author: arsrc
 */

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_


#include <iostream>
#include <cassert>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include "animation.hpp"
/*Classe que define os sprites que compõe
 * uma animação.
 */

Animation::Animation(sf::Texture *texture) :
		_texture(texture) {
}

Animation::~Animation() {
}

void Animation::setTexture(sf::Texture *texture) {
	_texture = texture;
}

sf::Texture* Animation::getTexture() const {
	return _texture;
}

size_t Animation::size() const {
	return _frames.size();
}

const sf::IntRect& Animation::getRect(size_t index) const {
	return _frames[index];
}

Animation& Animation::addFrame(const sf::IntRect &rect) {
	_frames.emplace_back(rect);
	return *this;
}

Animation& Animation::addFramesLine(int number_x, int number_y, int line) {
	const sf::Vector2u size = _texture->getSize();
	const float delta_x = size.x / float(number_x);
	const float delta_y = size.y / float(number_y);

	for (int i = 0; i < number_x; ++i)
		addFrame(sf::IntRect(i * delta_x, line * delta_y, delta_x, delta_y));
	return *this;
}
Animation& Animation::addFramesColumn(int number_x, int number_y, int column) {
	const sf::Vector2u size = _texture->getSize();
	const float delta_x = size.x / float(number_x);
	const float delta_y = size.y / float(number_y);
	for (int i = 0; i < number_y; ++i)
		addFrame(sf::IntRect(column * delta_x, i * delta_y, delta_x, delta_y));
	return *this;
}

AnimatedSprite::AnimatedSprite(Animation *animation, Status status,
		const sf::Time &deltaTime, bool loop, int repeat) :
		_delta(deltaTime), _loop(loop), _repeat(repeat), _status(status) {
	setAnimation(animation);
}

void AnimatedSprite::setAnimation(Animation *animation) {
	if (_animation != animation) {
		_animation = animation;
		_elapsed = sf::Time::Zero;
		_currentFrame = 0;
		setFrame(0, true);
	}
}

Animation* AnimatedSprite::getAnimation() const {
	return _animation;
}

void AnimatedSprite::setFrameTime(sf::Time deltaTime) {
	_delta = deltaTime;
}

sf::Time AnimatedSprite::getFrameTime() const {
	return _delta;
}

void AnimatedSprite::setLoop(bool loop) {
	_loop = loop;
}

bool AnimatedSprite::getLoop() const {
	return _loop;
}

void AnimatedSprite::setRepeat(int nb) {
	_repeat = nb;
}

int AnimatedSprite::getRepeat() const {
	return _repeat;
}

void AnimatedSprite::play() {
	_status = Playing;
}

void AnimatedSprite::pause() {
	_status = Paused;
}

void AnimatedSprite::stop() {
	_status = Stopped;
	_currentFrame = 0;
	setFrame(0, true);
}

AnimatedSprite::Status AnimatedSprite::getStatus() const {
	return _status;
}

void AnimatedSprite::setFrame(size_t index) {
	assert(_animation);
	_currentFrame = index % _animation->size();
	setFrame(_currentFrame, true);
}
void AnimatedSprite::setColor(const sf::Color &color) {
	_vertices[0].color = color;
	_vertices[1].color = color;
	_vertices[2].color = color;
	_vertices[3].color = color;
}

void AnimatedSprite::update(const sf::Time &deltaTime) {
	if (_status == Playing and _animation) {
		_elapsed += deltaTime;

		if (_elapsed > _delta) { //need to change frame
			_elapsed -= _delta;
			if (_currentFrame + 1 < _animation->size())
				++_currentFrame;
			else { //end of frame list
				_currentFrame = 0;

				if (not _loop) { //can we make another loop an the frames?
					--_repeat;
					if (_repeat <= 0) { //no, so we stop
						_status = Stopped;
					}
				}
			}
		}
		//update the frame
		setFrame(_currentFrame, false);
	}
}

void AnimatedSprite::setFrame(size_t index, bool resetTime) {
	if (_animation) {
		sf::IntRect rect = _animation->getRect(index);
		//update vertice position
		_vertices[0].position = sf::Vector2f(0.f, 0.f);
		_vertices[1].position = sf::Vector2f(0.f,
				static_cast<float>(rect.height));
		_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width),
				static_cast<float>(rect.height));
		_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width),
				0.f);
		//compute the texture coords
		float left = static_cast<float>(rect.left);
		float right = left + static_cast<float>(rect.width);
		float top = static_cast<float>(rect.top);
		float bottom = top + static_cast<float>(rect.height);
		//set the texture coords
		_vertices[0].texCoords = sf::Vector2f(left, top);
		_vertices[1].texCoords = sf::Vector2f(left, bottom);
		_vertices[2].texCoords = sf::Vector2f(right, bottom);
		_vertices[3].texCoords = sf::Vector2f(right, top);

	}
	if (resetTime)
		_elapsed = sf::Time::Zero;
}

void AnimatedSprite::draw(sf::RenderTarget &target,
		sf::RenderStates states) const {
	if (_animation and _animation->_texture) {
		states.transform *= getTransform();
		states.texture = _animation->_texture;
		target.draw(_vertices, 4, sf::Quads, states);
	}
}


#endif /* ANIMATION_HPP_ */
