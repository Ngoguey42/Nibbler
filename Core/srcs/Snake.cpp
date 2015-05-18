/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 17:22:59 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Snake.hpp"
#include "Game.hpp"
#include "ABlock.hpp"
#include "nibbler.h"

Snake::Snake(void)
{
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

float							Snake::getSpeed(void) const
{
	return (std::chrono::duration<float, std::milli>(_speed).count());
}

float							Snake::getMoveRatio(void) const
{
	return (std::chrono::duration<float, std::milli>(_lastMove).count() / getSpeed());
}

bool							Snake::isDie(void) const
{
	return (_die);
}

void							Snake::update(Game &game, std::chrono::steady_clock::duration t)
{
	if (_die)
		return ;
	_lastMove += t;
	while (_lastMove > _speed)
	{
		_direction = _nextDirection;
		_move(game);
		_lastMove -= _speed;
	}
}

void							Snake::kill(Game &game)
{
	game.setPaused(true);
	_die = true;
}

void							Snake::grow(void)
{
	_toGrow++;
	_speed -= _speed * 2 / 150;
}

bool							Snake::isChunk(int x, int y) const
{
	for (auto it = _chunks.begin(); it != _chunks.end(); ++it)
		if (x == it->first && y == it->second)
			return (true);
	return (false);
}

void							Snake::setNextDirection(int x, int y)
{
	_nextDirection.first = x;
	_nextDirection.second = y;
}

void							Snake::reset(Game const &game, int x, int y)
{
	while (_chunks.size() > 0)
		_chunks.pop_back();
	_lastMove = std::chrono::seconds(0);
	_toGrow = 0;
	_nextDirection = std::make_pair(0, 1);
	_die = false;
	_speed = std::chrono::milliseconds(INITIAL_SPEED);
	for (int i = 0; i < game.getInitialLength(); ++i)
		_chunks.emplace_front(Snake::Chunk(x, y++));
}

void							Snake::_collide(Game &game)
{
	Snake::Chunk	&head = *_chunks.begin();

	// Borders
	if (head.first < 0 || head.first >= game.getGameWidth()
		|| head.second < 0 || head.second >= game.getGameHeight())
		return (kill(game));
	// Eat itself
	for (auto it = ++_chunks.begin(); it != _chunks.end(); ++it)
		if (head == *it)
			return (kill(game));
	// Blocks
	for (IBlock *b : game.getBlocks())
		if (head.first == b->getX() && head.second == b->getY())
			static_cast<ABlock*>(b)->active(game);
}

void							Snake::_move(Game &game)
{
	Snake::Chunk	newChunk(*_chunks.begin());

	if (_toGrow > 0)
		_toGrow--;
	else
		_chunks.pop_back();
	newChunk.first += _direction.first;
	newChunk.second += _direction.second;
	if (game.isWallThrough())
	{
		if (newChunk.first < 0)
			newChunk.first = game.getGameWidth() - 1;
		if (newChunk.first >= game.getGameWidth())
			newChunk.first = 0;
		if (newChunk.second < 0)
			newChunk.second = game.getGameHeight() - 1;
		if (newChunk.second >= game.getGameHeight())
			newChunk.second = 0;
	}
	_chunks.emplace_front(newChunk);
	_collide(game);
}
