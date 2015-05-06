/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 19:05:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Snake.hpp"
#include "Game.hpp"
#include "IBonus.hpp"

Snake::Snake(int x, int y)
	: direction(0, 1), speed(std::chrono::milliseconds(INITIAL_SPEED)),
	die(false), _lastMove(0)
{
	chunks.emplace_front(Snake::Chunk(x, y -= 4));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
}

Snake::~Snake(void)
{
}

bool				Snake::collide(Game const &game)
{
	auto				head = chunks.begin();

	if (head->first < 0 || head->first >= game.gameWidth
		|| head->second < 0 || head->second >= game.gameHeight)
		return (die = true);
	for (auto it = chunks.begin(); it != chunks.end(); ++it)
		if (head->first == it->first && head->second == it->second
			&& head != it)
			return (die = true);
	return (false);
}

bool				Snake::isChunk(int x, int y)
{
	for (auto it = chunks.begin(); it != chunks.end(); ++it)
		if (x == it->first && y == it->second)
			return (true);
	return (false);
}

void				Snake::update(Game const &game, std::chrono::steady_clock::duration t)
{
	_lastMove += t;
	while (!die && _lastMove > speed)
	{
		_move(game);
		_lastMove -= speed;
	}
}

void				Snake::_move(Game const &game)
{
	Snake::Chunk		&head = *chunks.begin();

	for (auto it = game.bonus.begin(); it != game.bonus.end(); ++it)
		if (head.first == (*it)->getX() && head.second == (*it)->getY())
			(*it)->active(*this);
	chunks.pop_back();
	chunks.emplace_front(Snake::Chunk(head.first + direction.first,
		head.second + direction.second));
}
