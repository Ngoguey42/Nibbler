/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:48:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 17:49:05 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "SfmlUI.hpp"

extern "C"
{

IUI				*INIT_FUNCTION(std::pair<int, int> gameSize)
{
	return (new SfmlUI(gameSize));
}

}
