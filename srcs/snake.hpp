/**
 * @file snake.hpp
 * @author jang hun han (wkdgns720@naver.com)
 * @brief
 * @version 0.1
 * @date 2024-01-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "SFML/System/Clock.hpp"
#include "snakeGame.hpp"

class Snake
{
	public:
		Snake(float CircleSize);
		~Snake();

		void						move();
		void						grow();
		void						checkCollision();
		void						setDirection(sf::Vector2i dir);
		void						setCircleSize(float CircleSize);
		int							getLength() const;
		void						draw(sf::RenderWindow& window);
		sf::Vector2f				getHeadPosition();
		std::vector<sf::Vector2i>	getBody() const;
		bool 						checkFoodCollision(Food& food);
		sf::Vector2f				findClosestFood(const sf::Vector2f& headPosition, std::vector<Food>& foods, sf::RenderWindow& window);
		void						update();
		void						shrink();
	private:
		sf::Color getRandomColor();
		float	CircleSize;
		std::vector<sf::CircleShape> body;
		sf::Vector2f direction;
		sf::Clock clock;
};
