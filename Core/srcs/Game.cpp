/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 17:38:23 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <utility>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include "nibbler.h"
#include "ft_argv.h"
#include "Game.hpp"
#include "IUI.hpp"
#include "Event.hpp"
#include "IBlock.hpp"
#include "ABlock.hpp"
#include "GrowBlock.hpp"
#include "BonusBlock.hpp"
#include "WallBlock.hpp"
#include "WallSpawnBlock.hpp"

Game::Game(int argc, char **argv) throw(std::exception)
	: _uiLib(NULL), _ui(NULL),
	_initialLength(DEF_LENGTH), _initialWalls(-1),
	_paused(false), _fps(0), _snake()
{
	// Arguments
	t_args		args = ARGS(argc, argv);
	char const	*ui = INITIAL_UI;
	char		*tmp;

	while ((tmp = ft_argvopt(&args)) != NULL)
		if (strcmp(tmp, "ui") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--ui option need data");
			ui = ft_argvarg(&args);
		}
		else if (strcmp(tmp, "wall-through") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--wall-through option need data");
			_wallThrough = (ft_argvarg(&args)[0] == 'y') ? true : false;
		}
		else if (strcmp(tmp, "t") == 0)
			_wallThrough = true;
		else if (strcmp(tmp, "length") == 0 || strcmp(tmp, "l") == 0)
		{
			if (strcmp(tmp, "length") == 0 && !ARGS_DATA(args))
				throw std::invalid_argument("--length option need data");
			_initialLength = atoi(ft_argvarg(&args));
		}
		else if (strcmp(tmp, "wall") == 0 || strcmp(tmp, "w") == 0)
		{
			if (strcmp(tmp, "wall") == 0 && !ARGS_DATA(args))
				throw std::invalid_argument("--wall option need data");
			_initialWalls = atoi(ft_argvarg(&args));
		}
		else if (strcmp(tmp, "bonus-to-wall") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--bonus-to-wall option need data");
			_bonusToWall = (ft_argvarg(&args)[0] == 'y') ? true : false;
		}
		else if (strcmp(tmp, "b") == 0)
			_bonusToWall = false;
		else
			throw std::invalid_argument(std::string("Invalid option: ") += tmp);
	if ((tmp = ft_argvarg(&args)) == NULL)
		throw std::invalid_argument("Argument 'game_width' required");
	_gameWidth = atoi(tmp);
	if (_gameWidth < MIN_GAME_WIDTH || _gameWidth > MAX_GAME_WIDTH)
		throw std::invalid_argument("Invalid 'game_width' argument");
	if ((tmp = ft_argvarg(&args)) == NULL)
		throw std::invalid_argument("Argument 'game_height' required");
	_gameHeight = atoi(tmp);
	if (_gameHeight < MIN_GAME_HEIGHT || _gameHeight > MAX_GAME_HEIGHT)
		throw std::invalid_argument("Invalid 'game_width' argument");
	if (_initialWalls < 0)
		_initialWalls = DEF_WALL_COUNT;
	if (_initialLength < MIN_LENGTH || _initialLength > MAX_LENGTH)
		throw std::invalid_argument("Invalid 'length' argument");
	changeUI(ui);
	// Init
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
		EventType	event = _ui->getEvent();
		if (event != EVENT_NOPE)
			Event(event).process(*this);
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

int							Game::getPlayTime(void) const
{
	return (std::chrono::duration_cast<std::chrono::seconds>(_playTime).count());
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

std::list<IBlock*>			&Game::getBlocks(void)
{
	return (_blocks);
}

Snake						&Game::getSnake(void)
{
	return (_snake);
}

int							Game::getInitialLength(void) const
{
	return (_initialLength);
}

bool						Game::isWallThrough(void) const
{
	return (_wallThrough);
}

bool						Game::isBonusToWall(void) const
{
	return (_wallThrough);
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
	_playTime = std::chrono::seconds(0);
	_bonusInterval = std::chrono::seconds(BONUS_INTERVAL);
	_snake.reset(*this, INITIAL_X, INITIAL_Y);
	for (int i = 0; i < _initialWalls; ++i)
		spawn(new WallBlock());
#ifdef WALL_SPAWNER
	spawn(new WallSpawnBlock());
#endif
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
	_playTime += t;
	_bonusInterval -= t;
	if (_bonusInterval < std::chrono::seconds(0))
	{
		spawn(new BonusBlock(BONUS_TIMEOUT));
		_bonusInterval = std::chrono::seconds(BONUS_INTERVAL);		
	}
	_snake.update(*this, t);
	for (auto it = _blocks.begin(); it != _blocks.end(); ++it)
		if (static_cast<ABlock*>(*it)->shouldDestroy())
		{
			delete *it;
			it = _blocks.erase(it);
		}
	for (IBlock *b : _blocks)
		static_cast<ABlock*>(b)->update(*this, t);
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
		_ui = reinterpret_cast<IUI *(*)(std::pair<int, int>)>
			(init_func)(std::make_pair(_gameWidth, _gameHeight));
	}
	catch (std::exception &e)
	{
		dlclose(_uiLib);
		_ui = NULL;
		throw;
	}
	DEBUG("New UI loaded: " << name);
}
