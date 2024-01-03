/**
 * @file snake.cpp
 * @author jang hun han (wkdgns720@naver.com)
 * @brief
 * @version 0.1
 * @date 2024-01-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "snake.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "snakeGame.hpp"
#include <cmath>
#include <ratio>
#include <scoped_allocator>
#include <vector>
#include <iostream>

Snake::Snake(float circleSize) : CircleSize(circleSize), direction(1, 0)
{
	body.reserve(100);
	// 시드(seed)를 현재 시간으로 설정하여 랜덤성을 높임
	// std::srand(static_cast<unsigned>(std::time(nullptr)));
	for (int i = 0; i < 10; i++)
	{
		sf::CircleShape segment(CircleSize);
		// 랜덤한 위치에서 시작하도록 설정
		float randomX = static_cast<float>(std::rand() % SCREEN_W - 1); // 윈도우 가로 크기에 따라 조절
		float randomY = static_cast<float>(std::rand() % SCREEN_H - 1); // 윈도우 세로 크기에 따라 조절
		// std::cout << "Snake Random X: " << randomX << ", Y: " << randomY << std::endl;
		segment.setPosition(randomX, randomY);
		segment.setOrigin(segment.getRadius(), segment.getRadius());
		segment.setFillColor(getRandomColor());
		body.push_back(segment);
	}
}

Snake::~Snake() {}

void Snake::move()
{
	 for (size_t i = body.size(); i > 0; i--)
	 {
		float depth = 0.5f;
		sf::Vector2f previousPosition = body[i - 1].getPosition();
		sf::Vector2f currentPosition = body[i].getPosition();
		sf::Vector2f directionVector = (previousPosition - currentPosition);
		float distance = std::sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
		if (distance > CircleSize * depth)
		{
			directionVector = directionVector / distance * CircleSize * depth;
			body[i].setPosition(previousPosition - directionVector);
			body[i].setOrigin(body[i].getRadius(), body[i].getRadius());
		}
	}
	sf::Vector2f headPosition = body.front().getPosition();
	float		Speed = 1.0f;
	body.front().setPosition(headPosition + direction * CircleSize * Speed);
}

void Snake::grow()
{
	sf::CircleShape newSegment(CircleSize);
	sf::Vector2f lastSegmentPosition;

	if (!body.empty()) {
		lastSegmentPosition = body.back().getPosition();
		for (size_t i = 0; i < body.size(); i++) {
			body[i].setRadius(CircleSize);
		}
	}

	newSegment.setRadius(CircleSize);
	newSegment.setPosition(lastSegmentPosition);
	newSegment.setFillColor(getRandomColor());
	newSegment.setOrigin(newSegment.getRadius(), newSegment.getRadius());
	body.push_back(newSegment);
}

void Snake::setDirection(sf::Vector2i dir)
{
	sf::Vector2f headPosition = body.front().getPosition();
	sf::Vector2f directionVector = static_cast<sf::Vector2f>(dir - sf::Vector2i(headPosition));
	directionVector.x -= 10;
	directionVector.y -= 15;

	float length = std::sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
	if (length != 0)
	{
		direction = sf::Vector2f(directionVector.x / length, directionVector.y / length);
	}
}

bool Snake::checkFoodCollision(Food& food)
{
	if (!body.empty())
	{
		sf::FloatRect headBounds = body.front().getGlobalBounds();
		sf::FloatRect foodBounds(food.getPosition(), sf::Vector2f(FOODSIZE, FOODSIZE));
		if (headBounds.intersects(foodBounds))
		{
			if (body.size() < SNAMEMAXLENGHT)
				grow();
			return true;
		}
	}
	return false;
}

void Snake::setCircleSize(float plusSize)
{
	this->CircleSize = plusSize;
}

sf::Vector2f Snake::getHeadPosition()
{
	return sf::Vector2f(body.front().getPosition());
}

int Snake::getLength() const
{
	return static_cast<int>(body.size());
}

void Snake::draw(sf::RenderWindow& window)
{
	for (const auto& segment : body)
	{
		window.draw(segment);
	}
}

sf::Color Snake::getRandomColor() {
	// 랜덤 색상 생성
	return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

sf::Vector2f Snake::findClosestFood(const sf::Vector2f& headPosition, std::vector<Food>& foods, sf::RenderWindow& window)
{
	sf::Vector2f closestFoodPosition;
	float closestDistance = std::numeric_limits<float>::max();
	int index;

	if (body.size() == 0)
		return (headPosition);
	for (int i = 0; i < NUMFOOD; i++) {
		sf::Vector2f foodPosition = foods[i].getPosition();
		float distance = std::sqrt(std::pow(foodPosition.x - headPosition.x, 2) + std::pow(foodPosition.y - headPosition.y, 2));
		if (distance < closestDistance && !foods[i].getTarget()) {
			closestDistance = distance;
			closestFoodPosition = foodPosition;
			index = i;
		}
	}
	if (index != -1)
	{
		foods[index].setTarget(true);
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = headPosition;
		line[1].position = closestFoodPosition;
		line[0].color = sf::Color::Red;
		line[1].color = sf::Color::Red;
		window.draw(line);
		sf::Vector2f directionVector = closestFoodPosition - headPosition;
		float length = std::sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
		if (length != 0)
		{
			direction = directionVector / length;
		}
	}
	return closestFoodPosition;
}

void Snake::update()
{
	if (clock.getElapsedTime().asSeconds() > 0.5f)
	{
		shrink();
		clock.restart();
	}
}
void Snake::shrink()
{
	if (body.size() >= 1) {
		std::cout << "Before pop_back. Size: " << body.size() << std::endl;
		body.pop_back();
		std::cout << "After pop_back. Size: " << body.size() << std::endl;
	}
}
