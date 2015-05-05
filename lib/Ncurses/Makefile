# LOL

NAME := ../NcursesUI.so
C_DIR := srcs
H_DIRS := include
O_DIR := o
LIBS := 
CC := clang++
FLAGS := -Wall -Wextra -Werror -O2
LINKS := -fPIC -shared -lncurses
HEADS := -Iinclude -I../../include

all: $(NAME)

o/init.cpp.o: srcs/init.cpp include/NcursesUI.hpp
	@$(COMPILE)
o/NcursesUI.cpp.o: srcs/NcursesUI.cpp include/NcursesUI.hpp
	@$(COMPILE)

MSG_0 := printf '\033[0;32m%-18.18s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-18.18s\033[0;0m\n'

COMPILE = $(MSG_0) $< ; $(CC) $(FLAGS) $(HEADS) -c -o $@ $< || $(MSG_1) $<

O_FILES := o/init.cpp.o \
		o/NcursesUI.cpp.o

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
	@rm -f ../NcursesUI.so 2> /dev/null || true

re: fclean all

make:
	@bash './makemake.sh' re

.PHONY: all clean fclean re make
