/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:28 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 18:46:37 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SfmlUI.hpp"
#include "IGame.hpp"

SfmlUI::SfmlUI(std::pair<int, int> gameSize)
	: sf::RenderWindow(sf::VideoMode(gameSize.first * CHUNK_SIZE, 
		gameSize.second * CHUNK_SIZE), WINDOW_TITLE, sf::Style::Close)
{
	_events[sf::Keyboard::Up] = EVENT_UP;
	_events[sf::Keyboard::Right] = EVENT_RIGHT;
	_events[sf::Keyboard::Down] = EVENT_DOWN;
	_events[sf::Keyboard::Left] = EVENT_LEFT;
	_events[sf::Keyboard::Space] = EVENT_SPACE;
	_events[sf::Keyboard::R] = EVENT_R;
	_events[sf::Keyboard::Num1] = EVENT_1;
	_events[sf::Keyboard::Num2] = EVENT_2;
	_events[sf::Keyboard::Num3] = EVENT_3;
	_events[sf::Keyboard::Num4] = EVENT_4;
	_events[sf::Keyboard::Num5] = EVENT_5;
	_events[sf::Keyboard::Num6] = EVENT_6;
	_events[sf::Keyboard::Num7] = EVENT_7;
}

SfmlUI::~SfmlUI(void)
{
}

EventType			SfmlUI::getEvent(void)
{
	sf::Event		event;

	pollEvent(event);
	if (event.type == sf::Event::Closed)
		close();
	else if (event.type == sf::Event::KeyPressed)
	{
		if (_events.find(event.key.code) != _events.end())
			return (_events[event.key.code]);
		if (event.key.code == sf::Keyboard::Q || sf::Keyboard::Escape)
			close();
	}
	return (EVENT_NOPE);
}

void				SfmlUI::draw(IGame const &game)
{
	clear();
	_drawChunk(0, 0, sf::Color::Black);
	display();
	(void)game;
}

bool				SfmlUI::windowShouldClose(void) const
{
	return (!isOpen());
}

void				SfmlUI::_drawChunk(int, int, sf::Color)
{
	// static sf::RectangleShape	rect(sf::Vector2f(CHUNK_SIZE, CHUNK_SIZE));

	// rect.setFillColor(color);
	// rect.setPosition(x * CHUNK_SIZE, y * CHUNK_SIZE);
	// draw(rect);
}
