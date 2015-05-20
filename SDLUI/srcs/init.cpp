/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:23:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 19:15:19 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "SDLUI.hpp"

extern "C"
{

IUI				*INIT_FUNCTION(std::pair<int, int> gameSize)
{
	return (new SDLUI(gameSize));
}

}
