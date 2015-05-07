/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/07 14:30:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <utility>
#include <iostream>
#include <chrono>
#include <chrono>
#include <cstdlib>
#include "nibbler.h"
#include "Game.hpp"
#include "IUI.hpp"
#include "Event.hpp"
#include "GrowBonus.hpp"
#include "IBlock.hpp"
#include "ABlock.hpp"

Game::Game(void)
	: _uiLib(NULL), _ui(NULL),
	_gameWidth(GAME_WIDTH), _gameHeight(GAME_HEIGHT),
	_score(0), _paused(false), _snake(5, 5)
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
	auto		lastUpdate = std::chrono::steady_clock::now();
	auto		tmp = lastUpdate;

	while (_ui != NULL && !_ui->windowShouldClose())
	{
		tmp = std::chrono::steady_clock::now();
		while (true)
		{
			Event	event(_ui->getEvent());
			if (event.getType() == EVENT_NOPE)
				break ;
			event.process(*this);
		}
		_ui->draw(*this);
		_update(tmp - lastUpdate);
		lastUpdate = tmp;
	}
}

int							Game::getGameWidth(void) const
{
	return (_gameWidth);
}

int							Game::getGameHeight(void) const
{
	return (_gameHeight);
}

int							Game::getScore(void) const
{
	return (_score);
}

bool						Game::isPaused(void) const
{
	return (_paused);
}

std::list<IBlock*> const	&Game::getBlocks(void) const
{
	return (_blocks);
}

Snake						&Game::getSnake(void) const
{
	return (const_cast<Snake&>(_snake));
}

void						Game::setPaused(bool paused)
{
	_paused = paused;
}

void						Game::_update(std::chrono::steady_clock::duration t)
{
	if (_paused)
		return ;
	_snake.update(*this, t);
	for (auto it = _blocks.begin(); it != _blocks.end(); ++it)
		if (static_cast<ABlock*>(*it)->shouldDestroy())
			it = _blocks.erase(it);
	if (_snake.collide(*this))
		return ;
	if (_blocks.size() <= 0)
		_spawn(new GrowBonus());
}

void						Game::_spawn(ABlock *b)
{
	int			pos = _gameWidth * _gameHeight - _snake.getChunks().size();

	if (pos <= 0)
		return ;
	pos = rand() % pos;
	_blocks.push_back(b);
	for (int y = 0; y < _gameHeight; ++y)
		for (int x = 0; x < _gameWidth; ++x)
			if (!_snake.isChunk(x, y) && --pos < 0)
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
