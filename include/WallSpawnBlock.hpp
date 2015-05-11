/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WallSpawnBlock.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:44:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLSPAWNBLOCK_HPP
# define WALLSPAWNBLOCK_HPP

# include "nibbler.h"
# include "ABlock.hpp"

class	WallSpawnBlock : public ABlock
{
public:
	WallSpawnBlock(void);
	virtual ~WallSpawnBlock(void);

	virtual void			active(Game &game);
	virtual bool			shouldDestroy(void) const;

protected:

	bool					_eaten;

private:
	WallSpawnBlock(WallSpawnBlock const &src);
	WallSpawnBlock			&operator=(WallSpawnBlock const &rhs);
};

#endif
