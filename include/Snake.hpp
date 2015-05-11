/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 18:03:12 by jaguillo         ###   ########.fr       */
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
	Snake(int x, int y);
	virtual ~Snake(void);

// Shared
	virtual std::deque<Chunk> const	&getChunks(void) const;
	virtual bool					isChunk(int x, int y) const;

	virtual std::pair<int, int>		getDirection(void) const;

	virtual bool					isDie(void) const;
// -

	void							update(Game &game, std::chrono::steady_clock::duration t);

	void							kill(void);

	void							grow(int x, int y);

	void							setDirection(int x, int y);

protected:

	std::deque<Chunk>				_chunks;

	std::pair<int, int>				_direction;

	bool							_die;

	std::chrono::steady_clock::duration	_speed;
	std::chrono::steady_clock::duration	_lastMove;

	void							_collide(Game &game);
	void							_move(Game &game);

private:
	Snake(void);
	Snake(Snake const &src);
	Snake							&operator=(Snake const &rhs);
};

#endif
