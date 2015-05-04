/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 15:11:40 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GrowBonus.hpp"

GrowBonus::GrowBonus(void)
	: _eaten(false)
{
}

GrowBonus::~GrowBonus(void)
{
}

IBonus::Type	GrowBonus::getType(void) const
{
	return (IBonus::Type::GROW);
}

void			GrowBonus::active(Snake &)
{
	_eaten = true;
}

bool			GrowBonus::shouldDestroy(void) const
{
	return (_eaten);
}
