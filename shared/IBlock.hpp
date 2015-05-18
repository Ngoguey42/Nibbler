/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IBlock.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:55:20 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/15 17:42:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IBLOCK_HPP
# define IBLOCK_HPP

class	IBlock
{
public:
	enum	Type
	{
		GROW,
		WALL,
		WALL_SPAWN,
		BONUS,
		NOPE
	};

	virtual ~IBlock(void){}

	virtual int				getX(void) const = 0;
	virtual int				getY(void) const = 0;

	virtual Type			getType(void) const = 0;

protected:

private:
};

#endif
