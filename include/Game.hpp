/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 16:05:11 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <queue>
# include "IUI.hpp"
# include "Snake.hpp"

class	Game
{
public:
	Game(void);
	virtual ~Game(void);

	// getScore
	// getSnake
	// getEverything

protected:

	void					*_uiLib;
	IUI						*_ui;

	Snake					_snake;

	void					changeUI(char const *lib);

private:
	Game(Game const &src);
	Game					&operator=(Game const &rhs);
};

#endif
