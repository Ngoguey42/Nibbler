/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:28 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 20:11:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SfmlUI.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"

SfmlUI::SfmlUI(std::pair<int, int> gameSize)
	: sf::RenderWindow(sf::VideoMode(gameSize.first * CHUNK_SIZE, 
		gameSize.second * CHUNK_SIZE), WINDOW_TITLE, sf::Style::Close),
	_gameSize(gameSize),
	_line(sf::LinesStrip, 2)
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
	_line[0].color = sf::Color(GRID_COLOR);
	_line[1].color = sf::Color(GRID_COLOR);
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
	_drawGrid();
	// Draw blocks
	for (auto *b : game.getBlocks())
	{
		if (b->getType() == IBlock::WALL)
			_drawWallBlock(b->getX(), b->getY());
		else
			_drawChunk(b->getX(), b->getY(), _chunkColor(b->getType()));
	}
	// Draw snake
	for (auto &c : game.getSnake().getChunks())
		_drawChunk(c.first, c.second, sf::Color::Red);
	if (game.getSnake().isDie())
	{
		auto &head = *(game.getSnake().getChunks().begin());
		_drawChunk(head.first, head.second, sf::Color(240, 10, 10));
	}
	display();
}

bool				SfmlUI::windowShouldClose(void) const
{
	return (!isOpen());
}

sf::Color			SfmlUI::_chunkColor(IBlock::Type type)
{
	if (type == IBlock::GROW)
		return (sf::Color::Yellow);
	else if (type == IBlock::WALL_SPAWN)
		return (sf::Color(50, 50, 50));
	return (sf::Color::Black);
}

void				SfmlUI::_drawGrid(void)
{
	for (int y = 0; y < _gameSize.second; ++y)
	{
		_line[0].position = sf::Vector2f(0, y * CHUNK_SIZE);
		_line[1].position = sf::Vector2f(_gameSize.first * CHUNK_SIZE, y * CHUNK_SIZE);
		sf::RenderWindow::draw(_line);
	}
	for (int x = 0; x < _gameSize.first; ++x)
	{
		_line[0].position = sf::Vector2f(x * CHUNK_SIZE, 0);
		_line[1].position = sf::Vector2f(x * CHUNK_SIZE, _gameSize.second * CHUNK_SIZE);
		sf::RenderWindow::draw(_line);
	}
}

void				SfmlUI::_drawWallBlock(int x, int y)
{
	x *= CHUNK_SIZE;
	y *= CHUNK_SIZE;
	_line[0].position = sf::Vector2f(x, y);
	_line[1].position = sf::Vector2f(x + CHUNK_SIZE, y + CHUNK_SIZE);
	sf::RenderWindow::draw(_line);
	_line[0].position = sf::Vector2f(x + CHUNK_SIZE, y);
	_line[1].position = sf::Vector2f(x, y + CHUNK_SIZE);
	sf::RenderWindow::draw(_line);
}

void				SfmlUI::_drawChunk(int x, int y, sf::Color color)
{
	static sf::RectangleShape	rect(sf::Vector2f(CHUNK_SIZE, CHUNK_SIZE));

	rect.setFillColor(color);
	rect.setPosition(x * CHUNK_SIZE, y * CHUNK_SIZE);
	sf::RenderWindow::draw(rect);
}
