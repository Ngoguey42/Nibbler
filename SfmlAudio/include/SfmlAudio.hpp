/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlAudio.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:48:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 15:52:43 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFMLAUDIO_HPP
# define SFMLAUDIO_HPP

# include <SFML/Audio.hpp>
# include "nibbler.h"
# include "IAudio.hpp"

class	SfmlAudio : public IAudio
{
public:
	SfmlAudio(void);
	virtual ~SfmlAudio(void);

	void					play(Type type);

protected:

	sf::SoundBuffer			_buffers[IAudio::NOPE];
	sf::Sound				_sounds[IAudio::NOPE];

	char const				*_soundsLocations[IAudio::NOPE];

private:
	SfmlAudio(SfmlAudio const &src);
	SfmlAudio				&operator=(SfmlAudio const &rhs);
};

#endif
