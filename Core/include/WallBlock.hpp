/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WallBlock.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 17:17:36 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:29:36 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLBLOCK_HPP
# define WALLBLOCK_HPP

# include "nibbler.h"
# include "ABlock.hpp"

class	WallBlock : public ABlock
{
public:
	WallBlock(void);
	virtual ~WallBlock(void);

	virtual void			active(Game &game);
	virtual bool			shouldDestroy(void) const;

protected:

private:
	WallBlock(WallBlock const &src);
	WallBlock				&operator=(WallBlock const &rhs);
};

#endif
