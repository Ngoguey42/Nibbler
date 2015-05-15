/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:23:27 by jaguillo          #+#    #+#             */
//   Updated: 2015/05/15 14:52:15 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.h"
#include "Window.class.hpp"

extern "C"
{

Window			*INIT_FUNCTION(std::pair<int, int> gridSize)
{
	return (new Window(gridSize));
}

}
