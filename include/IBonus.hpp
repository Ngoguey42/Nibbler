/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IBonus.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:21:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 17:36:25 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IBONUS_HPP
# define IBONUS_HPP

# include "nibbler.h"

class	IBonus
{
public:
	enum	Type
	{
		GROW
	};

	IBonus(void){}
	virtual ~IBonus(void){}

	virtual void			setPos(int x, int y) = 0;
	virtual int				getX(void) const = 0;
	virtual int				getY(void) const = 0;

	virtual Type			getType(void) const = 0;
	virtual void			active(Snake &snake) = 0;
	virtual bool			shouldDestroy(void) const = 0;

protected:

private:
	IBonus(IBonus const &src);
	IBonus					&operator=(IBonus const &rhs);
};

#endif
