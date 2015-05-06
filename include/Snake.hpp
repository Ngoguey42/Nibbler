/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 19:05:22 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <deque>
# include <chrono>
# include "nibbler.h"

class	Snake
{
public:
	Snake(int x, int y);
	virtual ~Snake(void);

	typedef std::pair<int, int>	Chunk;

	void						update(Game const &game, std::chrono::steady_clock::duration t);

	bool						collide(Game const &game);

	bool						isChunk(int x, int y);

	std::deque<Chunk>			chunks;

	std::pair<int, int>			direction;

	std::chrono::steady_clock::duration	speed;

	bool						die;

protected:

	std::chrono::steady_clock::duration	_lastMove;

	void						_move(Game const &game);

private:
	Snake(void);
	Snake(Snake const &src);
	Snake						&operator=(Snake const &rhs);
};

#endif
