/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:23:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 19:25:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.h"
#include "Window.class.hpp"

extern "C"
{

Window			*INIT_FUNCTION(std::pair<int, int> gridSize, float cellSize)
{
	return (new Window(gridSize, cellSize));
}

}
