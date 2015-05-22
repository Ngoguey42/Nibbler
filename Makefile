# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/18 12:45:11 by jaguillo          #+#    #+#              #
#    Updated: 2015/05/22 15:53:26 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nibbler

RULES = clean fclean re

all: _all $(NAME)

$(NAME):
	@ln -s Core/$@ $@

_all:
	@make -C Core
	@make -C NcursesUI
	@make -C OpenGLUI
	@make -C SfmlUI
	@make -C SDLUI
	@make -C SfmlAudio

$(RULES):
	@make -C Core $@
	@make -C NcursesUI $@
	@make -C OpenGLUI $@
	@make -C SfmlUI $@
	@make -C SDLUI $@
	@make -C SfmlAudio $@

.PHONY: all _all $(RULES)
