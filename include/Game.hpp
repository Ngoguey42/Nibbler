/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 17:15:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <exception>
# include <list>
# include "nibbler.h"
# include "Snake.hpp"

class	Game
{
public:
	Game(void);
	virtual ~Game(void);

	void						start(void);

	int							gameWidth;
	int							gameHeight;

	int							score;
	bool						paused;
	std::pair<int, int>			direction;

	std::list<IBonus*>			bonus;

	Snake						snake;

	void						changeUI(char const *lib) throw(std::exception);

protected:

	void						*_uiLib;
	IUI							*_ui;

	void						_update(void);

private:
	Game(Game const &src);
	Game						&operator=(Game const &rhs);
};

#endif
