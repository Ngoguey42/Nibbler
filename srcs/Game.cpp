/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 17:55:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <iostream>
#include <chrono>
#include "nibbler.h"
#include "Game.hpp"
#include "Event.hpp"
#include "IUI.hpp"

Game::Game(void)
	: gameWidth(GAME_WIDTH), gameHeight(GAME_HEIGHT), snake(5, 5),
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
	std::chrono::steady_clock::time_point	lastUpdate;

	lastUpdate = std::chrono::steady_clock::now();
	while (_ui != NULL && !_ui->windowShouldClose())
	{
		while (true)
		{
			Event	event(_ui->getEvent());
			if (event.getType() == Event::Type::NOPE)
				break ;
			event.process(*this);
		}
		_ui->draw(*this);
		while ((std::chrono::steady_clock::now() - lastUpdate) > UPDATE_INTERVAL)
		{
			_update();
			lastUpdate += UPDATE_INTERVAL;
		}
	}
}

void						Game::_update(void)
{
	snake.update();
	// collisions and bonus
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
			(init_func)(std::make_pair(gameWidth, gameHeight), 35.f);
	}
	catch (std::exception &e)
	{
		dlclose(_uiLib);
		_ui = NULL;
		throw;
	}
	DEBUG("New UI loaded: " << name);
}
