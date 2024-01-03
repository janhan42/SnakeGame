/**
 * @file food.cpp
 * @author jang hun han (wkdgns720@naver.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SFML/Graphics/Color.hpp"
#include "food.hpp"
#include "snakeGame.hpp"
#include <iostream>

Food::Food(float size) : size(size), target(false)
{
	food.setRadius(size / 2.0f);
	static bool srandCalled = false;
	if (!srandCalled)
	{
		std::cout << "Seed: " << static_cast<unsigned>(time(nullptr)) << std::endl;
		srand(static_cast<unsigned>(time(nullptr)));
		srandCalled = true;
	}
	respawn(SCREEN_W - 1, SCREEN_H - 1);
	food.setFillColor(getRandomColor());
}

void	Food::respawn(int windowWidth, int windowHeight)
{
	float x = static_cast<float>(rand() % (windowWidth - static_cast<int>(size)));
	float y = static_cast<float>(rand() % (windowHeight - static_cast<int>(size)));

	std::cout << "Random X: " << x << ", Y: " << y << std::endl;
	position = sf::Vector2f(x, y);
	food.setPosition(position);
	food.setOrigin(food.getRadius(), food.getRadius());
}

void	Food::draw(sf::RenderWindow& window) const
{
	window.draw(food);
}

sf::Vector2f Food::getPosition() const
{
	return position;
}

sf::Color Food::getRandomColor()
{
	return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

sf::FloatRect Food::getGlobalBounds() const
{
	return food.getGlobalBounds();
}

void	Food::setTarget(bool setting)
{
	this->target = setting;
}

bool	Food::getTarget(){
	return this->target;
}
