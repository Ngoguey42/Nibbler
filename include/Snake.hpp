/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 16:01:04 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <queue>

class	Snake
{
public:
	Snake(int x, int y);
	virtual ~Snake(void);

	typedef std::pair<int, int>	Chunk;

	void						move(int x, int y);

protected:

	std::queue<Chunk>			_chunks;

private:
	Snake(void);
	Snake(Snake const &src);
	Snake						&operator=(Snake const &rhs);
};

#endif
