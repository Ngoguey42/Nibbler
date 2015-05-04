/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 15:18:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(int x, int y)
{
	_chunks.emplace_front(Snake::Chunk(x, y));
}

Snake::~Snake(void)
{
}

std::deque<Snake::Chunk> const	&Snake::getChunks(void) const
{
	return (_chunks);
}

void						Snake::move(int x, int y)
{
	Snake::Chunk						&last = *_chunks.begin();

	_chunks.pop_back();
	_chunks.emplace_front(Snake::Chunk(last.first + x, last.second + y));
}
