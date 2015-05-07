/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABlock.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:41:44 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/07 11:49:43 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABlock.hpp"

ABlock::ABlock(Type type)
	: _type(type), _pos(0, 0)
{
}

ABlock::~ABlock(void)
{
}

void			ABlock::setPos(int x, int y)
{
	_pos.first = x;
	_pos.second = y;
}

int				ABlock::getX(void) const
{
	return (_pos.first);
}

int				ABlock::getY(void) const
{
	return (_pos.second);
}

ABlock::Type	ABlock::getType(void) const
{
	return (_type);
}
