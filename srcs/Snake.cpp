/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 16:05:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(int x, int y)
{
	_chunks.emplace(Chunk(x, y));
}

Snake::~Snake(void)
{
}

void			Snake::move(int x, int y)
{
	_chunks.pop();
	_chunks.emplace(Chunk(x, y));
}
