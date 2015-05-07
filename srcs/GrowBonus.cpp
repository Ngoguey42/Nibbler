/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/07 13:42:52 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GrowBonus.hpp"
#include "Snake.hpp"

GrowBonus::GrowBonus(void)
	: ABlock(ABlock::GROW), _eaten(false)
{
}

GrowBonus::~GrowBonus(void)
{
}

void					GrowBonus::active(Snake &snake)
{
	_eaten = true;
	snake.grow(_pos.first, _pos.second);
}

bool					GrowBonus::shouldDestroy(void) const
{
	return (_eaten);
}
