/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:23:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/05 21:08:52 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "NcursesUI.hpp"

extern "C"
{

IUI				*INIT_FUNCTION(std::pair<int, int> gameSize)
{
	return (new NcursesUI(gameSize));
}

}
