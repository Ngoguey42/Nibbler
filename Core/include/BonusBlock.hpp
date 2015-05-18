/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BonusBlock.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 18:35:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUSBLOCK_HPP
# define BONUSBLOCK_HPP

# include "nibbler.h"
# include "ABlock.hpp"

class	BonusBlock : public ABlock
{
public:
	BonusBlock(std::chrono::steady_clock::duration timeout);
	virtual ~BonusBlock(void);

	virtual void			update(Game &game, std::chrono::steady_clock::duration t);
	virtual void			active(Game &game);
	virtual bool			shouldDestroy(void) const;

protected:

	bool					_eaten;

	std::chrono::steady_clock::duration	_timeout;

private:
	BonusBlock(void);
	BonusBlock(BonusBlock const &src);
	BonusBlock				&operator=(BonusBlock const &rhs);
};

#endif
