/**
 * @file food.hpp
 * @author jang hun han (wkdgns720@naver.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Graphics.hpp>

class Food
{
	public:
		Food(float size);

		void	respawn(int windowWidth, int windowHeight);
		void	draw(sf::RenderWindow& window) const;

		sf::Color 		getRandomColor();
		sf::Vector2f	getPosition() const;
		sf::FloatRect	getGlobalBounds() const;
		void			setTarget(bool setting);
		bool			getTarget();

	private:
		sf::CircleShape	food;
		sf::Vector2f	position;
		float			size;
		bool			target;
};
