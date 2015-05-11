/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 18:14:24 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Snake.hpp"
#include "Game.hpp"
#include "ABlock.hpp"

Snake::Snake(int x, int y)
	: _direction(0, 1), _die(false),
	_speed(std::chrono::milliseconds(INITIAL_SPEED)), _lastMove(0)
{
	_chunks.emplace_front(Snake::Chunk(x, y -= 4));
	_chunks.emplace_front(Snake::Chunk(x, ++y));
	_chunks.emplace_front(Snake::Chunk(x, ++y));
	_chunks.emplace_front(Snake::Chunk(x, ++y));
	_chunks.emplace_front(Snake::Chunk(x, ++y));
}

Snake::~Snake(void)
{
}

std::deque<Snake::Chunk> const	&Snake::getChunks(void) const
{
	return (_chunks);
}

std::pair<int, int>				Snake::getDirection(void) const
{
	return (_direction);
}

bool							Snake::isDie(void) const
{
	return (_die);
}

void							Snake::kill(void)
{
	_die = true;
}

void							Snake::grow(int x, int y)
{
	_chunks.emplace_back(Snake::Chunk(x, y));
}

bool							Snake::isChunk(int x, int y) const
{
	for (auto it = _chunks.begin(); it != _chunks.end(); ++it)
		if (x == it->first && y == it->second)
			return (true);
	return (false);
}

void							Snake::setDirection(int x, int y)
{
	_direction.first = x;
	_direction.second = y;
}

void							Snake::update(Game &game, std::chrono::steady_clock::duration t)
{
	_lastMove += t;
	while (!_die && _lastMove > _speed)
	{
		_move(game);
		_lastMove -= _speed;
	}
}

void							Snake::_collide(Game &game)
{
	Snake::Chunk	&head = *_chunks.begin();

	// Borders
	if (head.first < 0 || head.first >= game.getGameWidth()
		|| head.second < 0 || head.second >= game.getGameHeight())
		return (kill());
	// Eat itself
	for (auto it = _chunks.begin(); it != _chunks.end(); ++it)
		if (head.first == it->first && head.second == it->second && head != *it)
		return (kill());
	// Blocks
	for (auto it = game.getBlocks().begin(); it != game.getBlocks().end(); ++it)
		if (head.first == (*it)->getX() && head.second == (*it)->getY())
			static_cast<ABlock*>(*it)->active(game);
}

void							Snake::_move(Game &game)
{
	Snake::Chunk	newChunk(*_chunks.begin());

	_chunks.pop_back();
	newChunk.first += _direction.first;
	newChunk.second += _direction.second;
	_chunks.emplace_front(newChunk);
	_collide(game);
}
