# LOL

NAME := nibbler
C_DIR := srcs
H_DIRS := include common
O_DIR := o
LIBS := lib/OpenGL lib/Ncurses
CC := clang++
FLAGS := -std=c++14 -Wall -Wextra -Werror -g
LINKS := -Llib/Ncurses -Llib/OpenGL 
HEADS := -I include -I common

all: $(NAME)

o/ABlock.cpp.o: srcs/ABlock.cpp include/ABlock.hpp
	@$(COMPILE)
o/Event.cpp.o: srcs/Event.cpp common/nibbler.h include/Event.hpp include/Game.hpp
	@$(COMPILE)
o/Game.cpp.o: srcs/Game.cpp common/nibbler.h include/Game.hpp common/IUI.hpp include/Event.hpp include/GrowBonus.hpp common/IBlock.hpp include/ABlock.hpp
	@$(COMPILE)
o/GrowBonus.cpp.o: srcs/GrowBonus.cpp include/GrowBonus.hpp include/Snake.hpp
	@$(COMPILE)
o/main.cpp.o: srcs/main.cpp common/nibbler.h common/IUI.hpp include/Game.hpp
	@$(COMPILE)
o/Snake.cpp.o: srcs/Snake.cpp include/Snake.hpp include/Game.hpp include/ABlock.hpp
	@$(COMPILE)
lib/OpenGL:
	@make -C lib/OpenGL

lib/Ncurses:
	@make -C lib/Ncurses


MSG_0 := printf '\033[0;32m%-18.18s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-18.18s\033[0;0m\n'

COMPILE = $(MSG_0) $< ; $(CC) $(FLAGS) $(HEADS) -c -o $@ $< || $(MSG_1) $<

O_FILES := o/ABlock.cpp.o \
		o/Event.cpp.o \
		o/Game.cpp.o \
		o/GrowBonus.cpp.o \
		o/main.cpp.o \
		o/Snake.cpp.o

$(NAME): o/ $(LIBS) $(O_FILES)
	@$(MSG_0) $@ ; $(CC) $(FLAGS) -o $@ $(O_FILES) $(LINKS) && echo || $(MSG_1) $@

o/:
	@mkdir -p $@ 2> /dev/null || true

o/%:
	@mkdir -p $@ 2> /dev/null || true

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o 2> /dev/null || true

fclean: clean
	@rm -f nibbler 2> /dev/null || true

re: fclean all

make:
	@bash './makemake.sh' re

.PHONY: all clean fclean re make lib/OpenGL lib/Ncurses
