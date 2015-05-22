/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 17:46:50 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 14:18:14 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <exception>
#include <cmath>
#include <cstdlib>
#include "Settings.hpp"
#include "nibbler.h"
#include "ft_argv.h"

Settings::Settings(int argc, char **argv)
	: initialUI(INITIAL_UI),
	gameWidth(-1), gameHeight(-1),
	initialLength(DEF_LENGTH), initialWalls(-1),
	wallThrough(false), bonusToWall(true)
{
	t_args		args = ARGS(argc, argv);
	char		*tmp;

	// Options
	while ((tmp = ft_argvopt(&args)) != NULL)
	{
		int i = -1;
		while (Settings::_opts[++i].opt != NULL)
			if (strcmp(tmp, Settings::_opts[i].opt) == 0)
			{
				(this->*(Settings::_opts[i].f))(&args, tmp);
				break ;
			}
		if (Settings::_opts[i].opt == NULL)
			throw std::invalid_argument(std::string("Invalid option -- ") += tmp);
	}
	// Arguments
	if ((tmp = ft_argvarg(&args)) == NULL)
		throw std::invalid_argument("Argument 'game_width' required");
	gameWidth = atoi(tmp);
	if ((tmp = ft_argvarg(&args)) == NULL)
		throw std::invalid_argument("Argument 'game_height' required");
	gameHeight = atoi(tmp);
	// Invalid arguments
	if (gameWidth < MIN_GAME_WIDTH || gameWidth > MAX_GAME_WIDTH)
		throw std::invalid_argument("Invalid 'game_width' argument");
	if (gameHeight < MIN_GAME_HEIGHT || gameHeight > MAX_GAME_HEIGHT)
		throw std::invalid_argument("Invalid 'game_width' argument");
	if (initialLength < MIN_LENGTH || initialLength > MAX_LENGTH)
		throw std::invalid_argument("Invalid 'length' argument");
	// Default
	if (initialWalls < 0)
		initialWalls = INITIAL_WALLS;
	initialX = INITIAL_X;
	initialY = INITIAL_Y;
	initialSpeed = INITIAL_SPEED;
	bonusInterval = std::chrono::seconds(BONUS_INTERVAL);
	bonusTimeout = std::chrono::seconds(static_cast<int>(BONUS_TIMEOUT));
}

Settings::~Settings(void)
{
}

void			Settings::_optUI(t_args *args, char *)
{
	static char const	*uis[] = {UI_1, UI_2, UI_3, UI_4};

	if (!ARGS_DATA(*args))
		throw std::invalid_argument("--ui option need a value");
	char *tmp = ft_argvarg(args);
	if (tmp == NULL)
		throw std::invalid_argument("--ui option need a value");
	if (strlen(tmp) == 1 && *tmp >= '1' && *tmp <= '4')
		initialUI = uis[*tmp - '1'];
	else
		initialUI = tmp;
}

void			Settings::_optWallThrough(t_args *args, char *opt)
{
	if (strcmp(opt, "t") == 0)
	{
		wallThrough = true;
		return ;
	}
	if (!ARGS_DATA(*args))
		throw std::invalid_argument("--wall-through option need a value");
	char *tmp = ft_argvarg(args);
	if (tmp == NULL)
		throw std::invalid_argument("-wall-through option need a value");
	wallThrough = (tmp[0] == 'y') ? true : false;
}

void			Settings::_optLength(t_args *args, char *opt)
{
	if (strcmp(opt, "length") == 0 && !ARGS_DATA(*args))
		throw std::invalid_argument("--length option need a value");
	char *tmp = ft_argvarg(args);
	if (tmp == NULL)
		throw std::invalid_argument("-l option need a value");
	initialLength = atoi(tmp);
}

void			Settings::_optWalls(t_args *args, char *opt)
{
	if (strcmp(opt, "wall") == 0 && !ARGS_DATA(*args))
		throw std::invalid_argument("--wall option need a value");
	char *tmp = ft_argvarg(args);
	if (tmp == NULL)
		throw std::invalid_argument("-w option need a value");
	initialWalls = atoi(tmp);
}

void			Settings::_optBonusToWall(t_args *args, char *opt)
{
	if (strcmp(opt, "b") == 0)
	{
		bonusToWall = false;
		return ;
	}
	if (!ARGS_DATA(*args))
		throw std::invalid_argument("--bonus-to-wall option need a value");
	char *tmp = ft_argvarg(args);
	if (tmp == NULL)
		throw std::invalid_argument("-bonus-to-wall option need a value");
	bonusToWall = (tmp[0] == 'y') ? true : false;
}

Settings::Opt	Settings::_opts[] = {
	{"ui", &Settings::_optUI},
	{"t", &Settings::_optWallThrough},
	{"wall-through", &Settings::_optWallThrough},
	{"l", &Settings::_optLength},
	{"length", &Settings::_optLength},
	{"w", &Settings::_optWalls},
	{"wall", &Settings::_optWalls},
	{"b", &Settings::_optBonusToWall},
	{"bonus-to-wall", &Settings::_optBonusToWall},
	{NULL, NULL}
};
