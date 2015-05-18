/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 18:11:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <utility>
# include <deque>
# include <chrono>
# include "nibbler.h"
# include "ISnake.hpp"

class	Snake : public ISnake
{
public:
	Snake(void);
	virtual ~Snake(void);

// Shared
	virtual std::deque<Chunk> const	&getChunks(void) const;
	virtual float					getSpeed(void) const;
	virtual float					getMoveRatio(void) const;
	virtual std::pair<int, int>		getDirection(void) const;

	virtual bool					isChunk(int x, int y) const;

	virtual bool					isDie(void) const;
// -

	void							update(Game &game, std::chrono::steady_clock::duration t);

	void							kill(Game &game);

	void							grow(void);

	void							setNextDirection(int x, int y);

	void							reset(Game const &game);

protected:

	std::deque<Chunk>				_chunks;

	std::pair<int, int>				_direction;
	std::pair<int, int>				_nextDirection;

	int								_toGrow;

	bool							_die;

	std::chrono::steady_clock::duration	_speed;
	std::chrono::steady_clock::duration	_lastMove;

	void							_collide(Game &game);
	void							_move(Game &game);

private:
	Snake(Snake const &src);
	Snake							&operator=(Snake const &rhs);
};

#endif
