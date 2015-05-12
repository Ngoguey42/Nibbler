/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 15:21:40 by jaguillo         ###   ########.fr       */
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
// -

class	Game;
class	Snake;
class	IUI;
class	Event;
class	ABlock;
class	GrowBlock;

/*
** ========================================================================== **
** Settings
*/

# define GAME_WIDTH			17
# define GAME_HEIGHT		20

# define INITIAL_X			GAME_WIDTH / 2
# define INITIAL_Y			5
# define INITIAL_LENGTH		4
# define INITIAL_SPEED		130

// # define WALL_THROUGH

# define WALL_COUNT			3

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
** Libs
*/

# define INIT_FUNCTION		init

# define UI_1				"lib/OpenGLUI.so"
# define UI_2				"lib/NcursesUI.so"

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
