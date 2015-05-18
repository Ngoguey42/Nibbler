# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/18 12:45:11 by jaguillo          #+#    #+#              #
#    Updated: 2015/05/18 12:58:16 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: nibbler ncurses opengl sfml

nibbler:
	@make -C Core
	@ln -s Core/$@ $@

ncurses:
	@make -C NcursesUI

opengl:
	@make -C OpenGLUI

sfml:
	# @make -C SfmlUI

clean:
	@make -C Core clean
	@make -C NcursesUI clean
	@make -C OpenGLUI clean
	# @make -C SfmlUI clean

fclean:
	@make -C Core fclean
	@make -C NcursesUI fclean
	@make -C OpenGLUI fclean
	# @make -C SfmlUI fclean

re:
	@make -C Core re
	@make -C NcursesUI re
	@make -C OpenGLUI re
	# @make -C SfmlUI re
