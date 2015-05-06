/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 14:28:42 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 16:19:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.h"
#include "Event.hpp"
#include "Game.hpp"
#include <iostream>

Event::Event(Event::Type type)
	: _type(type)
{
}

Event::~Event(void)
{
}

Event::Type			Event::getType(void) const
{
	return (_type);
}

void				Event::process(Game &game)
{
	if (_type < 0 || _type >= Type::NOPE)
		return ;
	(this->*(_events[_type]))(game);
}

void				Event::_processUp(Game &game)
{
	if (game.paused || game.snake.direction.second == 1)
		return ;
	game.snake.direction = std::make_pair(0, -1);
}

void				Event::_processRight(Game &game)
{
	if (game.paused || game.snake.direction.first == -1)
		return ;
	game.snake.direction = std::make_pair(1, 0);
}

void				Event::_processDown(Game &game)
{
	if (game.paused || game.snake.direction.second == -1)
		return ;
	game.snake.direction = std::make_pair(0, 1);
}

void				Event::_processLeft(Game &game)
{
	if (game.paused || game.snake.direction.first == 1)
		return ;
	game.snake.direction = std::make_pair(-1, 0);
}

void				Event::_processSpace(Game &game)
{
	game.paused = !game.paused;
}

void				Event::_process1(Game &game)
{
	game.paused = true;
	game.changeUI(UI_1);
}

void				Event::_process2(Game &game)
{
	game.paused = true;
	game.changeUI(UI_2);
}

void				Event::_process3(Game &)
{
}

void				Event::_process4(Game &)
{
}

void				Event::_process5(Game &)
{
}

void				Event::_process6(Game &)
{
}

void				Event::_process7(Game &)
{
}

Event::event_t		Event::_events[Type::NOPE]  = {
	&Event::_processUp,
	&Event::_processRight,
	&Event::_processDown,
	&Event::_processLeft,
	&Event::_processSpace,
	&Event::_process1,
	&Event::_process2,
	&Event::_process3,
	&Event::_process4,
	&Event::_process5,
	&Event::_process6,
	&Event::_process7
};
