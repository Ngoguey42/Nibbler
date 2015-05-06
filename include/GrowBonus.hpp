/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 17:36:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROWBONUS_HPP
# define GROWBONUS_HPP

# include <utility>
# include "nibbler.h"
# include "IBonus.hpp"

class	GrowBonus : public IBonus
{
public:
	GrowBonus(void);
	virtual ~GrowBonus(void);

	virtual void			setPos(int x, int y);
	virtual int				getX(void) const;
	virtual int				getY(void) const;

	virtual Type			getType(void) const;
	virtual void			active(Snake &snake);
	virtual bool			shouldDestroy(void) const;

protected:

	std::pair<int, int>		_pos;
	bool					_eaten;

private:
	GrowBonus(GrowBonus const &src);
	GrowBonus				&operator=(GrowBonus const &rhs);
};

#endif
