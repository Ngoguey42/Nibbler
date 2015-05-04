/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 13:37:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROWBONUS_HPP
# define GROWBONUS_HPP

# include "nibbler.h"
# include "IBonus.hpp"

class	GrowBonus : public IBonus
{
public:
	GrowBonus(void);
	virtual ~GrowBonus(void);

	virtual Type		getType(void) const;
	virtual void		active(Snake &snake);
	virtual bool		shouldDestroy(void) const;

protected:

	bool				_eaten;

private:
	GrowBonus(GrowBonus const &src);
	GrowBonus			&operator=(GrowBonus const &rhs);
};

#endif
