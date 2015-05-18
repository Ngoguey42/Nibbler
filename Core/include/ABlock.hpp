/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABlock.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:21:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/15 17:56:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABLOCK_HPP
# define ABLOCK_HPP

# include <utility>
# include <chrono>
# include "nibbler.h"
# include "IBlock.hpp"

class	ABlock : public IBlock
{
public:
	ABlock(Type type);
	virtual ~ABlock(void);

// Shared
	virtual int				getX(void) const;
	virtual int				getY(void) const;

	virtual Type			getType(void) const;
// -

	void					setPos(int x, int y);

	virtual void			update(Game &game, std::chrono::steady_clock::duration t);

	virtual void			active(Game &game) = 0;
	virtual bool			shouldDestroy(void) const = 0;

protected:

	Type					_type;

	std::pair<int, int>		_pos;

private:
	ABlock(void);
	ABlock(ABlock const &src);
	ABlock					&operator=(ABlock const &rhs);
};

#endif
