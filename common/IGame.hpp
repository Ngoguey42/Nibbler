/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGame.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:55:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:36:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGAME_HPP
# define IGAME_HPP

# include <list>
# include "nibbler.h"

class	IGame
{
public:
	IGame(void){}
	virtual ~IGame(void){}

	virtual int							getGameWidth(void) const = 0;
	virtual int							getGameHeight(void) const = 0;

	virtual int							getScore(void) const = 0;
	virtual int							getFPS(void) const = 0;
	virtual bool						isPaused(void) const = 0;

	virtual bool						isBlock(int x, int y) const = 0;

	virtual std::list<IBlock*> const	&getBlocks(void) const = 0;
	virtual ISnake const				&getSnake(void) const = 0;

protected:

private:
	IGame(IGame const &src);
	IGame								&operator=(IGame const &rhs);
};

#endif
