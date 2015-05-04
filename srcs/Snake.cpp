/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 17:54:29 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(int x, int y)
	: direction(0, 1)
{
	chunks.emplace_front(Snake::Chunk(x, y -= 4));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
	chunks.emplace_front(Snake::Chunk(x, ++y));
}

Snake::~Snake(void)
{
}

void						Snake::update(void)
{
	Snake::Chunk		&last = *chunks.begin();

	chunks.pop_back();
	chunks.emplace_front(Snake::Chunk(last.first + direction.first,
		last.second + direction.second));
}
