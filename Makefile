# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/18 12:45:11 by jaguillo          #+#    #+#              #
#    Updated: 2015/05/29 15:50:35 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := nibbler

SUB_PREFIX := sub_

EXTERN := extern/ftconstexpr

all: $(NAME)

$(NAME): $(EXTERN) $(SUB_PREFIX)all
	@ln -fs Core/$@ $@

clean: $(SUB_PREFIX)clean

fclean: $(SUB_PREFIX)fclean

re: fclean all

$(EXTERN):
	@git submodule update --init "$@"

$(SUB_PREFIX)%:
	@make -C Core $(subst $(SUB_PREFIX),,$@)
	@make -C NcursesUI $(subst $(SUB_PREFIX),,$@)
	@make -C OpenGLUI $(subst $(SUB_PREFIX),,$@)
	@make -C SfmlUI $(subst $(SUB_PREFIX),,$@)
	@make -C SDLUI $(subst $(SUB_PREFIX),,$@)
	@make -C SfmlAudio $(subst $(SUB_PREFIX),,$@)

.PHONY: all clean fclean re $(SUB_PREFIX)% $(EXTERN)
