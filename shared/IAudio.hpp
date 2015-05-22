/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAudio.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:49:09 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 15:34:02 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IAUDIO_HPP
# define IAUDIO_HPP

class	IAudio
{
public:
	enum	Type
	{
		EAT,
		BONUS_APPEAR,
		BONUS_EAT,
		BONUS_DIE,
		DIE,
		NOPE
	};

	virtual ~IAudio(void){}

	virtual void		play(Type type) = 0;

protected:

private:
};

#endif
