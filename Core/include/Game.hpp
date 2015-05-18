/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 17:55:54 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <exception>
# include <list>
# include "nibbler.h"
# include "IGame.hpp"
# include "Snake.hpp"
# include "Settings.hpp"

class	Game : public IGame
{
public:
	Game(int argc, char **argv) throw(std::exception);
	virtual ~Game(void);

// Shared
	virtual int							getGameWidth(void) const;
	virtual int							getGameHeight(void) const;

	virtual int							getScore(void) const;
	virtual int							getFPS(void) const;
	virtual int							getPlayTime(void) const;
	virtual bool						isPaused(void) const;

	virtual bool						isBlock(int x, int y) const;

	virtual std::list<IBlock*> const	&getBlocks(void) const;
	virtual Snake const					&getSnake(void) const;
// -

	void								start(void);

	void								setPaused(bool paused);

	void								addScore(int add);

	std::list<IBlock*>					&getBlocks(void);
	Snake								&getSnake(void);

	Settings const						&getSettings(void) const;

	void								spawn(ABlock *block);

	void								reset(void);
	void								_destroyGame(void);

	void								changeUI(char const *lib) throw(std::exception);

protected:

	void								*_uiLib;
	IUI									*_ui;

	Settings							_settings;

	std::chrono::steady_clock::duration	_playTime;
	std::chrono::steady_clock::duration	_bonusInterval;

	int									_score;
	bool								_paused;
	int									_fps;

	std::list<IBlock*>					_blocks;

	Snake								_snake;

	void								_update(std::chrono::steady_clock::duration t);

private:
	Game(void);
	Game(Game const &src);
	Game								&operator=(Game const &rhs);
};

#endif
