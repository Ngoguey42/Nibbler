/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 20:02:44 by jaguillo         ###   ########.fr       */
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
#include "IBlock.hpp"
#include "ABlock.hpp"
#include "GrowBlock.hpp"
#include "WallBlock.hpp"
#include "WallSpawnBlock.hpp"

Game::Game(void)
	: _uiLib(NULL), _ui(NULL),
	_gameWidth(GAME_WIDTH), _gameHeight(GAME_HEIGHT),
	_paused(false), _fps(0), _snake()
{
	srand(time(NULL));
	reset();
}

Game::~Game(void)
{
	if (_ui != NULL)
	{
		delete _ui;
		dlclose(_uiLib);
	}
	_destroyGame();
}

void						Game::start(void)
{
	auto		lastUpdate = std::chrono::steady_clock::now();
	auto		lastFPS = std::chrono::steady_clock::now();
	int			frames = 0;
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
		if ((tmp - lastFPS) > std::chrono::seconds(1))
		{
			_fps = frames;
			lastFPS = tmp;
			frames = 0;
		}
		_ui->draw(*this);
		frames++;
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

int							Game::getFPS(void) const
{
	return (_fps);
}

bool						Game::isPaused(void) const
{
	return (_paused);
}

bool						Game::isBlock(int x, int y) const
{
	for (IBlock *b : _blocks)
		if (b->getX() == x && b->getY() == y)
			return (true);
	return (false);
}

std::list<IBlock*> const	&Game::getBlocks(void) const
{
	return (_blocks);
}

Snake const					&Game::getSnake(void) const
{
	return (_snake);
}

Snake						&Game::getSnake(void)
{
	return (_snake);
}

void						Game::setPaused(bool paused)
{
	_paused = paused;
}

void						Game::addScore(int add)
{
	_score += add;
}

void						Game::spawn(ABlock *b)
{
	int			pos = _gameWidth * _gameHeight;

	pos -= _snake.getChunks().size();
	pos -= _blocks.size();
	if (pos <= 0)
		return ;
	pos = rand() % pos;
	_blocks.push_back(b);
	for (int y = 0; y < _gameHeight; ++y)
		for (int x = 0; x < _gameWidth; ++x)
			if (!_snake.isChunk(x, y) && !isBlock(x, y) && --pos < 0)
			{
				b->setPos(x, y);
				return ;
			}
}

void						Game::reset(void)
{
	_destroyGame();
	_score = 0;
	_snake.reset(INITIAL_X, INITIAL_Y);
	for (int i = 0; i < WALL_COUNT; ++i)
		spawn(new WallBlock());
	spawn(new WallSpawnBlock());
	spawn(new GrowBlock());
}

void						Game::_destroyGame(void)
{
	for (IBlock *b : _blocks)
		delete b;
	_blocks.clear();
}

void						Game::_update(std::chrono::steady_clock::duration t)
{
	if (_paused)
		return ;
	_snake.update(*this, t);
	for (auto it = _blocks.begin(); it != _blocks.end(); ++it)
		if (static_cast<ABlock*>(*it)->shouldDestroy())
		{
			delete *it;
			it = _blocks.erase(it);
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
