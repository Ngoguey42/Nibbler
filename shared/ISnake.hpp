/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISnake.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:54:19 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 16:47:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISNAKE_HPP
# define ISNAKE_HPP

# include <utility>
# include <deque>
# include <chrono>
# include "nibbler.h"

class	ISnake
{
public:
	typedef std::pair<int, int>		Chunk;

	virtual ~ISnake(void){}

	virtual std::deque<Chunk> const	&getChunks(void) const = 0;
	virtual float					getSpeed(void) const = 0;
	virtual float					getMoveRatio(void) const = 0;
	virtual std::pair<int, int>		getDirection(void) const = 0;

	virtual bool					isChunk(int x, int y) const = 0;

	virtual bool					isDie(void) const = 0;

protected:

private:
};

#endif
