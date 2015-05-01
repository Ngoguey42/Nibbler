/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 19:52:37 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <exception>
# include "nibbler.h"
# include "Snake.hpp"

class	Game
{
public:
	Game(void);
	virtual ~Game(void);

	// getScore
	// getSnake
	// getEverything

	void					start(void);

	void					changeUI(char const *lib) throw(std::exception);

protected:

	int						_gameWidth;
	int						_gameHeight;

	Snake					_snake;

	void					*_uiLib;
	IUI						*_ui;

private:
	Game(Game const &src);
	Game					&operator=(Game const &rhs);
};

#endif
