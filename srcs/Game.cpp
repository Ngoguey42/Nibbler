/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 15:53:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <iostream>
#include <ctime>
#include "nibbler.h"
#include "Game.hpp"
#include "Event.hpp"
#include "IUI.hpp"

Game::Game(void)
	: _gameWidth(GAME_WIDTH), _gameHeight(GAME_HEIGHT), _snake(2, 2),
	_uiLib(NULL), _ui(NULL)
{
}

Game::~Game(void)
{
	if (_ui != NULL)
	{
		delete _ui;
		dlclose(_uiLib);
	}
}

void						Game::start(void)
{
	clock_t		lastUpdate;

	lastUpdate = clock();
	while (_ui != NULL && !_ui->windowShouldClose())
	{
		// while (true)
		// {
		// 	Event	event(_ui->getEvent());
		// 	if (event.getType() == Event::Type::NOPE)
		// 		break ;
		// 	event.process(*this);
		// }
		_ui->draw();
		while ((clock() - lastUpdate) > UPDATE_INTERVAL)
		{
			_update();
			lastUpdate += UPDATE_INTERVAL;
		}
	}
}

void						Game::_update(void)
{
	_snake.move(_direction.first, _direction.second);
}

Snake const					&Game::getSnake(void) const
{
	return (_snake);
}

int							Game::getScore(void) const
{
	return (_score);
}

std::list<IBonus*> const	&Game::getBonus(void) const
{
	return (_bonus);
}

std::pair<int, int>			Game::getGameSize(void) const
{
	return (std::pair<int, int>(_gameWidth, _gameHeight));
}

bool						Game::isPaused(void) const
{
	return (_paused);
}

void						Game::setDirection(int x, int y)
{
	_direction = std::pair<int, int>(x, y);
}

void						Game::setPaused(bool paused)
{
	_paused = paused;
}

void						Game::changeUI(char const *name) throw(std::exception)
{
	void		*init_func;

	if (_ui != NULL) // Delete old UI if any
	{
		DEBUG("Close old UI");
		delete _ui;
		_ui = NULL;
		dlclose(_uiLib);
	}
	// Try to load library
	if ((_uiLib = dlopen(name, RTLD_LAZY | RTLD_LOCAL)) == NULL)
		throw std::runtime_error(std::string(name) + ": Cannot load library");
	// Search init function
	if ((init_func = dlsym(_uiLib, STR(INIT_FUNCTION))) == NULL)
	{
		dlclose(_uiLib);
		throw std::runtime_error("Incomplete library");
	}
	// Try to init UI
	try
	{
		_ui = reinterpret_cast<IUI *(*)(std::pair<int, int>, float)>
			(init_func)(std::make_pair(_gameWidth, _gameHeight), 35.f);
	}
	catch (std::exception &e)
	{
		dlclose(_uiLib);
		_ui = NULL;
		throw;
	}
	DEBUG("New UI loaded: " << name);
}
