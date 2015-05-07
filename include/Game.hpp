/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/07 14:29:49 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <exception>
# include <list>
# include "nibbler.h"
# include "IGame.hpp"
# include "Snake.hpp"

class	Game : public IGame
{
public:
	Game(void);
	virtual ~Game(void);

// Shared
	virtual int							getGameWidth(void) const;
	virtual int							getGameHeight(void) const;

	virtual int							getScore(void) const;

	virtual bool						isPaused(void) const;

	virtual std::list<IBlock*> const	&getBlocks(void) const;
	virtual Snake						&getSnake(void) const;
// -

	void								start(void);

	void								setPaused(bool paused);

	void								changeUI(char const *lib) throw(std::exception);

protected:

	void								*_uiLib;
	IUI									*_ui;

	int									_gameWidth;
	int									_gameHeight;

	int									_score;
	bool								_paused;

	std::list<IBlock*>					_blocks;

	Snake								_snake;

	void								_update(std::chrono::steady_clock::duration t);

	void								_spawn(ABlock *block);

private:
	Game(Game const &src);
	Game								&operator=(Game const &rhs);
};

#endif
