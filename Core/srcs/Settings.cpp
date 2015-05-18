/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 17:46:50 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 18:21:56 by jaguillo         ###   ########.fr       */
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
		if (std::strcmp(tmp, "ui") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--ui option need data");
			initialUI = ft_argvarg(&args);
		}
		else if (std::strcmp(tmp, "wall-through") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--wall-through option need data");
			wallThrough = (ft_argvarg(&args)[0] == 'y') ? true : false;
		}
		else if (std::strcmp(tmp, "t") == 0)
			wallThrough = true;
		else if (std::strcmp(tmp, "length") == 0 || std::strcmp(tmp, "l") == 0)
		{
			if (std::strcmp(tmp, "length") == 0 && !ARGS_DATA(args))
				throw std::invalid_argument("--length option need data");
			initialLength = atoi(ft_argvarg(&args));
		}
		else if (std::strcmp(tmp, "wall") == 0 || std::strcmp(tmp, "w") == 0)
		{
			if (std::strcmp(tmp, "wall") == 0 && !ARGS_DATA(args))
				throw std::invalid_argument("--wall option need data");
			initialWalls = atoi(ft_argvarg(&args));
		}
		else if (std::strcmp(tmp, "bonus-to-wall") == 0)
		{
			if (!ARGS_DATA(args))
				throw std::invalid_argument("--bonus-to-wall option need data");
			bonusToWall = (ft_argvarg(&args)[0] == 'y') ? true : false;
		}
		else if (std::strcmp(tmp, "b") == 0)
			bonusToWall = false;
		else
			throw std::invalid_argument(std::string("Invalid option: ") += tmp);
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
