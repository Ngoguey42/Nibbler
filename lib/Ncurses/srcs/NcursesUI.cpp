/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:30 by juloo             #+#    #+#             */
/*   Updated: 2015/05/05 21:09:25 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesUI.hpp"
#include "Event.hpp"

NcursesUI::NcursesUI(std::pair<int, int> gameSize)
	: _gameSize(gameSize), _shouldClose(false)
{
}

NcursesUI::~NcursesUI(void)
{
}

Event::Type		NcursesUI::getEvent(void)
{
	return (Event::NOPE);
}

void			NcursesUI::draw(Game const &)
{
}

bool			NcursesUI::windowShouldClose(void) const
{
	return (_shouldClose);
}
