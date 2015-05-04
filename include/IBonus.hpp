/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IBonus.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:21:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 13:36:06 by jaguillo         ###   ########.fr       */
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

	virtual Type		getType(void) const = 0;
	virtual void		active(Snake &snake) = 0;
	virtual bool		shouldDestroy(void) const = 0;

protected:

private:
	IBonus(IBonus const &src);
	IBonus				&operator=(IBonus const &rhs);
};

#endif
