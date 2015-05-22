/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlAudio.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:51:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 18:02:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SfmlAudio.hpp"

SfmlAudio::SfmlAudio(void)
	: _soundsLocations{
		"SfmlAudio/misc/eat.wav",
		NULL,
		"SfmlAudio/misc/bonus_eat.wav",
		"SfmlAudio/misc/bonus_die.wav",
		"SfmlAudio/misc/die.wav"
	}
{
	for (int i = 0; i < IAudio::NOPE; ++i)
	{
		if (_soundsLocations[i] == NULL)
			continue ;
		if (!_buffers[i].loadFromFile(_soundsLocations[i]))
			_soundsLocations[i] = NULL;
		_sounds[i].setBuffer(_buffers[i]);
	}
}

SfmlAudio::~SfmlAudio(void)
{
}

void				SfmlAudio::play(IAudio::Type type)
{
	if (type < 0 || type >= IAudio::NOPE || _soundsLocations[type] == NULL)
		return ;
	_sounds[type].play();
}
