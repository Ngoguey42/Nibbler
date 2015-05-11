/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WallBlock.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 17:18:17 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:30:22 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WallBlock.hpp"
#include "Snake.hpp"
#include "Game.hpp"

WallBlock::WallBlock(void)
	: ABlock(ABlock::WALL)
{
}

WallBlock::~WallBlock(void)
{
}

void					WallBlock::active(Game &game)
{
	game.getSnake().kill();
}

bool					WallBlock::shouldDestroy(void) const
{
	return (false);
}
