/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/01 19:57:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

class	Game;
class	Snake;
class	IUI;

# define GAME_WIDTH			12
# define GAME_HEIGHT		20

# define INIT_FUNCTION		init

# define STR_VALUE(s)		#s
# define STR(s)				STR_VALUE(s)

# define PRINT(msg)			std::cout << msg << std::endl;

# define DEBUG(msg)			PRINT("Debug: " << msg)

#endif
