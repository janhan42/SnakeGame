/**
 * @file snakeGame.cpp
 * @author jang hun han (wkdgns720@naver.com)
 * @brief
 * @version 0.1
 * @date 2024-01-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "SFML/Window/Mouse.hpp"
#include <iostream>
#include "food.hpp"
#include "snake.hpp"
#include "snakeGame.hpp"

static void	initSnakeFood(std::vector<Snake>& snakes, std::vector<Food>& foods)
{
	for (int i = 0; i < NUMFOOD; i++)
	{
		foods.push_back(Food(FOODSIZE));
	}
	for (int i = 0; i < NUMSNAKE; i++)
	{
		snakes.push_back(Snake(SNAKESIZE));
	}
}

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Snake Game");
	window.setFramerateLimit(60);
	std::vector<Snake>	snakes; // vector로 Snake 생성
	std::vector<Food>	foods; // vector로 Food생성
	initSnakeFood(snakes, foods); // 각 개수만큼 push_back

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		for (size_t i = 0; i < snakes.size(); i++) {
			for (size_t j = 0; j < foods.size(); j++) {
				if (snakes[i].checkFoodCollision(foods[j])) {
					foods[j].respawn(window.getSize().x, window.getSize().y);
				}
			}
		}

		window.clear(sf::Color(240, 240, 240)); // window Clear
		for (auto& food : foods)
			food.setTarget(false);
		for (auto& snake : snakes)
		{
			sf::Vector2f closestFoodPosition = snake.findClosestFood(snake.getHeadPosition(), foods, window);
			// closestFood follow
			sf::Vector2i mousePosition(static_cast<int>(closestFoodPosition.x + FOODSIZE), static_cast<int>(closestFoodPosition.y + FOODSIZE));
			// Mouse follow
			// sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			snake.setDirection(mousePosition);
			// snake.update(0.5f);
			snake.move();
			snake.draw(window);
		}
		for (auto& food : foods)
		{
			food.draw(window);
		}
		window.display();
	}
	return (0);
}
