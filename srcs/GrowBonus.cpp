/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 18:58:49 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GrowBonus.hpp"
#include "Snake.hpp"

GrowBonus::GrowBonus(void)
	: _pos(0, 0), _eaten(false)
{
}

GrowBonus::~GrowBonus(void)
{
}

void					GrowBonus::setPos(int x, int y)
{
	_pos.first = x;
	_pos.second = y;
}

IBonus::Type			GrowBonus::getType(void) const
{
	return (IBonus::Type::GROW);
}

int						GrowBonus::getX(void) const
{
	return (_pos.first);
}

int						GrowBonus::getY(void) const
{
	return (_pos.second);
}

void					GrowBonus::active(Snake &snake)
{
	_eaten = true;
	snake.chunks.emplace_back(Snake::Chunk(_pos.first, _pos.second));
}

bool					GrowBonus::shouldDestroy(void) const
{
	return (_eaten);
}
