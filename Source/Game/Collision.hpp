#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

auto GetPlayerCollider(sf::Sprite &player) -> sf::FloatRect {
	auto bounds = player.getGlobalBounds();
	sf::FloatRect rect;

	rect.left = bounds.left;
	rect.width = bounds.width;
	rect.top = bounds.top + bounds.height / 2;
	rect.height = bounds.height / 2;

	return rect;
}

auto GetEnemyCollider(sf::Sprite &enemy) -> sf::FloatRect {
	auto bounds = enemy.getGlobalBounds();
	sf::FloatRect rect;

	rect.left = bounds.left;
	rect.width = bounds.width;
	rect.top = bounds.top + bounds.height / 2;
	rect.height = bounds.height / 2;

	return rect;
}

auto GetColliderShape(const sf::FloatRect &rect) -> sf::RectangleShape {
	sf::RectangleShape r;
	r.setSize( { rect.width, rect.height });
	r.setPosition(rect.left, rect.top);
	r.setFillColor( { 200, 0, 0, 95 });

	return r;
}
