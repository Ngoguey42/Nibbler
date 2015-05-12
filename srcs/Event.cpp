/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 14:28:42 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 18:05:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.h"
#include "Event.hpp"
#include "Game.hpp"
#include <iostream>

Event::Event(EventType type)
	: _type(type)
{
}

Event::~Event(void)
{
}

EventType			Event::getType(void) const
{
	return (_type);
}

void				Event::process(Game &game)
{
	if (_type < 0 || _type >= EVENT_NOPE)
		return ;
	(this->*(_events[_type]))(game);
}

void				Event::_processUp(Game &game)
{
	if (game.isPaused() || game.getSnake().getDirection().second == 1)
		return ;
	game.getSnake().setDirection(0, -1);
}

void				Event::_processRight(Game &game)
{
	if (game.isPaused() || game.getSnake().getDirection().first == -1)
		return ;
	game.getSnake().setDirection(1, 0);
}

void				Event::_processDown(Game &game)
{
	if (game.isPaused() || game.getSnake().getDirection().second == -1)
		return ;
	game.getSnake().setDirection(0, 1);
}

void				Event::_processLeft(Game &game)
{
	if (game.isPaused() || game.getSnake().getDirection().first == 1)
		return ;
	game.getSnake().setDirection(-1, 0);
}

void				Event::_processSpace(Game &game)
{
	game.setPaused(!game.isPaused());
}

void				Event::_processR(Game &game)
{
	game.reset();
}

void				Event::_process1(Game &game)
{
	game.setPaused(true);
	game.changeUI(UI_1);
}

void				Event::_process2(Game &game)
{
	game.setPaused(true);
	game.changeUI(UI_2);
}

void				Event::_process3(Game &game)
{
	game.setPaused(true);
	game.changeUI(UI_3);
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

Event::event_t		Event::_events[EVENT_NOPE]  = {
	&Event::_processUp,
	&Event::_processRight,
	&Event::_processDown,
	&Event::_processLeft,
	&Event::_processSpace,
	&Event::_processR,
	&Event::_process1,
	&Event::_process2,
	&Event::_process3,
	&Event::_process4,
	&Event::_process5,
	&Event::_process6,
	&Event::_process7
};
