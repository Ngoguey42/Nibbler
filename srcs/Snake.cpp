/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 17:15:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(int x, int y)
{
	chunks.emplace_front(Snake::Chunk(x, y));
	chunks.emplace_front(Snake::Chunk(x - 1, y));
	chunks.emplace_front(Snake::Chunk(x - 2, y));
}

Snake::~Snake(void)
{
}

void						Snake::move(int x, int y)
{
	Snake::Chunk		&last = *chunks.begin();

	chunks.pop_back();
	chunks.emplace_front(Snake::Chunk(last.first + x, last.second + y));
}
