/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 15:53:28 by jaguillo         ###   ########.fr       */
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

	Snake const					&getSnake(void) const;
	std::list<IBonus*> const	&getBonus(void) const;
	int							getScore(void) const;
	std::pair<int, int>			getGameSize(void) const;
	bool						isPaused(void) const;

	void						setDirection(int x, int y);

	void						setPaused(bool paused);

	void						changeUI(char const *lib) throw(std::exception);

protected:

	int							_gameWidth;
	int							_gameHeight;

	int							_score;
	bool						_paused;
	std::pair<int, int>			_direction;

	std::list<IBonus*>			_bonus;

	Snake						_snake;

	void						*_uiLib;
	IUI							*_ui;

	void						_update(void);

private:
	Game(Game const &src);
	Game						&operator=(Game const &rhs);
};

#endif
