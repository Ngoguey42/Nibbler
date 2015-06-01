/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:15 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 15:42:58 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include <utility>
#include <chrono>
#include <cstdlib>

#include "nibbler.h"
#include "Game.hpp"

#include "IUI.hpp"
#include "Event.hpp"
#include "IBlock.hpp"
#include "ABlock.hpp"
#include "GrowBlock.hpp"
#include "BonusBlock.hpp"
#include "WallBlock.hpp"
#include "WallSpawnBlock.hpp"
#include "IAudio.hpp"

Game::Game(int argc, char **argv) throw(std::exception)
	: _uiLib(NULL), _ui(NULL), _audioLib(NULL), _audio(NULL),
	_settings(argc, argv),
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
	return (_settings.gameWidth);
}

int							Game::getGameHeight(void) const
{
	return (_settings.gameHeight);
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

IAudio						*Game::getAudio(void) const
{
	return (_audio);
}

Settings const				&Game::getSettings(void) const
{
	return (_settings);
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
	int			pos = _settings.gameWidth * _settings.gameHeight;

	pos -= _snake.getChunks().size();
	pos -= _blocks.size();
	if (pos <= 0)
		return ;
	pos = rand() % pos;
	_blocks.push_back(b);
	for (int y = 0; y < _settings.gameHeight; ++y)
		for (int x = 0; x < _settings.gameWidth; ++x)
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
	_bonusInterval = _settings.bonusInterval;
	_snake.reset(*this);
	for (int i = 0; i < _settings.initialWalls; ++i)
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
		spawn(new BonusBlock(_settings.bonusTimeout));
		if (_audio != NULL)
			_audio->play(IAudio::BONUS_APPEAR);
		_bonusInterval = _settings.bonusInterval;		
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

void						Game::changeAudio(char const *name) throw(std::exception)
{
	void		*init_func;

	if (_audio != NULL)
	{
		delete _audio;
		_audio = NULL;
		dlclose(_audioLib);
	}
	if ((_audioLib = dlopen(name, RTLD_LAZY | RTLD_NOW | RTLD_LOCAL)) == NULL)
		throw std::runtime_error((std::string(name) += ": ") += dlerror());
	if ((init_func = dlsym(_audioLib, STR(INIT_FUNCTION))) == NULL)
	{
		dlclose(_audioLib);
		throw std::runtime_error(std::string(name) += "Incompatible library");
	}
	try
	{
		_audio = reinterpret_cast<IAudio *(*)(void)>(init_func)();
	}
	catch (std::exception &e)
	{
		dlclose(_audioLib);
		_audio = NULL;
		throw ;
	}
}

void						Game::changeUI(char const *name) throw(std::exception)
{
	void		*init_func;

	if (_ui != NULL) // Delete old UI if any
	{
		delete _ui;
		_ui = NULL;
		dlclose(_uiLib);
	}
	// Try to load library
	if ((_uiLib = dlopen(name, RTLD_LAZY | RTLD_NOW | RTLD_LOCAL)) == NULL)
		throw std::runtime_error((std::string(name) += ": ") += dlerror());
	// Search init function
	if ((init_func = dlsym(_uiLib, STR(INIT_FUNCTION))) == NULL)
	{
		dlclose(_uiLib);
		throw std::runtime_error(std::string(name) += "Incompatible library");
	}
	// Try to init UI
	try
	{
		_ui = reinterpret_cast<IUI *(*)(std::pair<int, int>)>
			(init_func)(std::make_pair(_settings.gameWidth, _settings.gameHeight));
		_ui->init();
	}
	catch (std::exception &e)
	{
		dlclose(_uiLib);
		_ui = NULL;
		throw ;
	}
}
