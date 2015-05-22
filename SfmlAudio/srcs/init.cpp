/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:47:03 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 15:52:15 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include "nibbler.h"
#include "SfmlAudio.hpp"

extern "C"
{

IAudio				*INIT_FUNCTION(void)
{
	return (new SfmlAudio());
}

}
