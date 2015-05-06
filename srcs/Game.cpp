/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 17:42:04 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <utility>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include "nibbler.h"
#include "Game.hpp"
#include "IUI.hpp"
#include "Event.hpp"
#include "GrowBonus.hpp"

Game::Game(void)
	: gameWidth(GAME_WIDTH), gameHeight(GAME_HEIGHT), snake(5, 5),
	_uiLib(NULL), _ui(NULL)
{
	srand(time(NULL));
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
		while (!snake.die && (std::chrono::steady_clock::now() - lastUpdate) > UPDATE_INTERVAL)
		{
			_update();
			lastUpdate += UPDATE_INTERVAL;
		}
	}
}

void						Game::_update(void)
{
	if (paused)
		return ;
	snake.update();
	if (snake.collide(*this))
		return ;
	if (bonus.size() <= 0)
		_spawn(new GrowBonus());
}

void						Game::_spawn(IBonus *b)
{
	int			pos = gameWidth * gameHeight - snake.chunks.size();

	pos = rand() % pos;
	bonus.push_back(b);
	for (int y = 0; y < gameHeight; ++y)
		for (int x = 0; x < gameWidth; ++x)
			if (--pos < 0)
			{
				b->setPos(x, y);
				return ;
			}
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
