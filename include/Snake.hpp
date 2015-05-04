/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 17:23:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <deque>

class	Snake
{
public:
	Snake(int x, int y);
	virtual ~Snake(void);

	typedef std::pair<int, int>	Chunk;

	void						update(void);

	std::deque<Chunk>			chunks;

	std::pair<int, int>			direction;

protected:

private:
	Snake(void);
	Snake(Snake const &src);
	Snake						&operator=(Snake const &rhs);
};

#endif
