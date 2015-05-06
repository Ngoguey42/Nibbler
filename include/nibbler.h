/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 19:25:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

/*
** ========================================================================== **
** Prototypes
*/

class	Game;
class	Snake;
class	IUI;
class	Event;
class	IBonus;
class	GrowBonus;

/*
** ========================================================================== **
** Settings
*/

# define GAME_WIDTH			13
# define GAME_HEIGHT		19

# define INITIAL_SPEED		130

/*
** ========================================================================== **
** Libs
*/

# define INIT_FUNCTION		init

# define UI_1				"lib/OpenGL.so"
# define UI_2				"lib/NcursesUI.so"

/*
** ========================================================================== **
** Utils
*/

# define STR_VALUE(s)		#s
# define STR(s)				STR_VALUE(s)

# define PRINT(msg)			std::cout << msg << std::endl;

# define DEBUG(msg)			PRINT("Debug: " << msg)

#endif
