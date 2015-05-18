/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Settings.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 17:46:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 18:22:29 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include <chrono>

# define DEF_LENGTH			4
# define MIN_LENGTH			3
# define MAX_LENGTH			(gameHeight / 2)

# define INITIAL_WALLS		(gameWidth * gameHeight / 60)

# define INITIAL_X			(gameWidth / 2)
# define INITIAL_Y			(gameHeight / 2 - initialLength)

# define INITIAL_SPEED		150

# define BONUS_INTERVAL		15
# define BONUS_TIMEOUT		std::sqrt(gameWidth * gameWidth + gameHeight * gameHeight) / 7.f + 2.f

# define MIN_GAME_WIDTH		10
# define MAX_GAME_WIDTH		30
# define MIN_GAME_HEIGHT	10
# define MAX_GAME_HEIGHT	40

class	Settings
{
public:
	Settings(int argc, char **argv);
	virtual ~Settings(void);

	char const			*initialUI;

	int					gameWidth;
	int					gameHeight;

	int					initialX;
	int					initialY;

	int					initialSpeed;

	std::chrono::steady_clock::duration	bonusInterval;
	std::chrono::steady_clock::duration	bonusTimeout;

	int					initialLength;
	int					initialWalls;

	bool				wallThrough;
	bool				bonusToWall;

protected:

private:
	Settings(void);
	Settings(Settings const &src);
	Settings			&operator=(Settings const &rhs);
};

#endif
