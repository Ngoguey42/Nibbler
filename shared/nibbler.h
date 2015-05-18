/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 13:50:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

/*
** ========================================================================== **
** Prototypes
*/

// Shared
class	IGame;
class	ISnake;
class	IBlock;
class	IUI;
// -

class	Game;
class	Snake;
class	Event;
class	ABlock;
class	GrowBlock;
class	WallBlock;
class	WallSpawnBlock;

/*
** ========================================================================== **
** Settings
*/

# define INITIAL_LENGTH		8
# define INITIAL_X			(_gameWidth / 2)
# define INITIAL_Y			(_gameHeight / 2 - INITIAL_LENGTH)

# define INITIAL_SPEED		150

# define WALL_THROUGH
// # define WALL_SPAWNER

# define BONUS_INTERVAL		15
# define BONUS_TIMEOUT		std::sqrt(_gameWidth * _gameWidth + _gameHeight * _gameHeight) / 7.f + 2.f
# define BONUS_TOWALL

# define WALL_COUNT			(_gameWidth * _gameHeight / 60)

# define MIN_GAME_WIDTH		10
# define MAX_GAME_WIDTH		30
# define MIN_GAME_HEIGHT	10
# define MAX_GAME_HEIGHT	40

/*
** ========================================================================== **
** Types
*/

enum	EventType
{
	EVENT_UP,
	EVENT_RIGHT,
	EVENT_DOWN,
	EVENT_LEFT,
	EVENT_SPACE,
	EVENT_R,
	EVENT_1,
	EVENT_2,
	EVENT_3,
	EVENT_4,
	EVENT_5,
	EVENT_6,
	EVENT_7,
	EVENT_NOPE
};

/*
** ========================================================================== **
** UIs
*/

# define WINDOW_TITLE		":: Nibbler ::"

# define INIT_FUNCTION		init

# define UI_1				"OpenGLUI/OpenGLUI.so"
# define UI_2				"NcursesUI/NcursesUI.so"
# define UI_3				"SfmlUI/SfmlUI.so"

# define INITIAL_UI			UI_2

/*
** ========================================================================== **
** Utils
*/

// # define EACH(it,c)			auto it = (c).begin(); it != (c).end(); ++it

# define STR_VALUE(s)		#s
# define STR(s)				STR_VALUE(s)

# define PRINT(msg)			std::cout << msg << std::endl;

# define DEBUG(msg)			PRINT("Debug: " << msg)

#endif
