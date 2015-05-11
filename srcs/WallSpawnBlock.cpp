/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WallSpawnBlock.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 18:47:23 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WallSpawnBlock.hpp"
#include "WallBlock.hpp"
#include "Game.hpp"
#include "Snake.hpp"

WallSpawnBlock::WallSpawnBlock(void)
	: ABlock(ABlock::WALL_SPAWN), _eaten(false)
{
}

WallSpawnBlock::~WallSpawnBlock(void)
{
}

void					WallSpawnBlock::active(Game &game)
{
	_eaten = true;
	game.addScore(5);
	game.spawn(new WallBlock());
	game.spawn(new WallSpawnBlock());
}

bool					WallSpawnBlock::shouldDestroy(void) const
{
	return (_eaten);
}
