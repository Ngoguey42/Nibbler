/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 19:57:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <iostream>
#include "nibbler.h"
#include "IUI.hpp"
#include "Game.hpp"

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

void			Game::start(void)
{
	while (_ui != NULL && !_ui->windowShouldClose())
		_ui->draw();
}

void			Game::changeUI(char const *name) throw(std::exception)
{
	void			*init_func;

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
		_ui = reinterpret_cast<IUI *(*)(std::pair<int, int>, float)>(init_func)(std::make_pair(_gameWidth, _gameHeight), 35.f);
	}
	catch (std::exception &e)
	{
		dlclose(_uiLib);
		_ui = NULL;
		throw;
	}
	DEBUG("New UI loaded: " << name);
}
