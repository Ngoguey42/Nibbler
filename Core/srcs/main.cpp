/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/18 17:09:13 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "nibbler.h"
#include "Game.hpp"

int				main(int argc, char **argv)
{
	try
	{
		Game	game(argc, argv);
		game.start();
	}
	catch (std::invalid_argument &e)
	{
		PRINT("\033[31mError: " << e.what() << "\033[0m");
		PRINT("Usage: " << argv[0] << " [opt] <game_width> <game_height>");
		PRINT("\tgame_width                 The width of the map in blocks ("
			STR(MIN_GAME_WIDTH) " to " STR(MAX_GAME_WIDTH) ")");
		PRINT("\tgame_height                The height of the map in blocks ("
			STR(MIN_GAME_HEIGHT) " to " STR(MAX_GAME_HEIGHT) ")");
		PRINT("Options:");
		PRINT("\t--ui=<1-3>                 Set initial ui");
		PRINT("\t--wall-through=<yes/no>    Wall through (Default 'no')");
		PRINT("\t-t                         --wall-through=yes");
		PRINT("\t--length=<length>");
		PRINT("\t--l <length>               Set initial length");
		PRINT("\t--wall=<count>");
		PRINT("\t-w <count>                 Set wall count");
		PRINT("\t--bonus-to-wall=<yes/no>   Bonus turn into wall (Default 'yes')");
		PRINT("\t-b                         --bonus-to-wall=no");
		PRINT("In game:");
		PRINT("\tArrows                     Change direction");
		PRINT("\tSpace                      Toggle pause");
		PRINT("\tQ/ESC                      Quit");
		PRINT("\tR                          Restart the game");
		PRINT("\t1-3                        Change UI");
		return (2);
	}
	catch (std::exception &e)
	{
		PRINT("\033[31mError: " << e.what() << "\033[0m");
		return (1);
	}
	return (0);
}
