/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 18:08:10 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Snake.hpp"
#include "Game.hpp"

Snake::Snake(int x, int y)
	: direction(0, 1), die(false)
{
	chunks.emplace_front(Snake::Chunk(x, y -= 4));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
}

Snake::~Snake(void)
{
}

bool				Snake::collide(Game const &game)
{
	Chunk				&head = *chunks.begin();

	if (head.first < 0 || head.first >= game.gameWidth
		|| head.second < 0 || head.second >= game.gameHeight)
		return (die = true);
	for (auto it = chunks.begin(); it != chunks.end(); ++it)
		if (head.first == it->first && head.second == it->second
			&& head != *it)
			return (die = true);
	return (false);
}

void				Snake::update(void)
{
	Snake::Chunk		&last = *chunks.begin();

	chunks.pop_back();
	chunks.emplace_front(Snake::Chunk(last.first + direction.first,
		last.second + direction.second));
}
