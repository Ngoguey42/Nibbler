/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/13 15:46:54 by jaguillo         ###   ########.fr       */
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
		game.changeUI(INITIAL_UI);
		game.start();
	}
	catch (std::invalid_argument &e)
	{
		PRINT("Error: " << e.what());
		PRINT("Usage: " << argv[0] << " game_width game_height");
		PRINT("\tgame_width\tThe width of the map in blocks ("
			STR(MIN_GAME_WIDTH) " to " STR(MAX_GAME_WIDTH) ")")
		PRINT("\tgame_height\tThe height of the map in blocks ("
			STR(MIN_GAME_HEIGHT) " to " STR(MAX_GAME_HEIGHT) ")")
		PRINT("In game:");
		PRINT("\tArrows\t\tChange direction");
		PRINT("\tSpace\t\tToggle pause");
		PRINT("\tQ/ESC\t\tQuit");
		PRINT("\tR\t\tRestart the game");
		PRINT("\t1-3\t\tChange UI");
		return (2);
	}
	catch (std::exception &e)
	{
		PRINT("Error: " << e.what());
		return (1);
	}
	return (0);
}
