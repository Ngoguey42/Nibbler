# LOL

NAME := ../OpenGL.so
C_DIR := srcs
H_DIRS := include ../../common
O_DIR := o
LIBS := 
CC := clang++
FLAGS := -Wall -Wextra -Werror -g -std=c++14
LINKS := -fPIC -shared -L ~/.brew/lib -l glfw3 -l GLEW -framework OpenGL
HEADS := -I include -I ../../common -I ~/.brew/include

all: $(NAME)

o/init.cpp.o: srcs/init.cpp include/Window.class.hpp
	@$(COMPILE)
o/Window.class.cpp.o: srcs/Window.class.cpp include/Window.class.hpp
	@$(COMPILE)
o/Window.draw.cpp.o: srcs/Window.draw.cpp include/Window.class.hpp
	@$(COMPILE)

MSG_0 := printf '\033[0;32m%-21.21s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-21.21s\033[0;0m\n'

COMPILE = $(MSG_0) $< ; $(CC) $(FLAGS) $(HEADS) -c -o $@ $< || $(MSG_1) $<

O_FILES := o/init.cpp.o \
		o/Window.class.cpp.o \
		o/Window.draw.cpp.o

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
	@rm -f ../OpenGL.so 2> /dev/null || true

re: fclean all

make:
	@bash './makemake.sh' re

.PHONY: all clean fclean re make
