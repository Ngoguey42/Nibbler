/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBlock.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:29:48 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROWBLOCK_HPP
# define GROWBLOCK_HPP

# include "nibbler.h"
# include "ABlock.hpp"

class	GrowBlock : public ABlock
{
public:
	GrowBlock(void);
	virtual ~GrowBlock(void);

	virtual void			active(Game &game);
	virtual bool			shouldDestroy(void) const;

protected:

	bool					_eaten;

private:
	GrowBlock(GrowBlock const &src);
	GrowBlock				&operator=(GrowBlock const &rhs);
};

#endif
