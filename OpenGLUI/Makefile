#
# ../OpenGLUI.so
#
# Makefile
#

#
# Config
#

# Project name
NAME := OpenGLUI.so

# Project directories
DIRS := srcs include ../shared

# Obj directory
O_DIR := o

# Number of threads
THREADS := 4

# Cpp compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# Clang++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2 -std=c++14 -g

# Linking flags
LD_FLAGS := -fPIC -shared -L ~/.brew/lib -lglfw3 -lGLEW -framework OpenGL

# Clang++ include flags
CPP_HEADS := -Iinclude -I../shared -I ~/.brew/include

#
# Internal
#

O_FILES := o/srcs/Window.class.o \
	o/srcs/Window.draw.o \
	o/srcs/init.o

MSG_0 := printf '\033[0;32m%-21.21s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-21.21s\033[0;0m\n'

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && echo || $(MSG_1) $@

o/srcs/Window.class.o: srcs/Window.class.cpp include/Window.class.hpp ../shared/nibbler.h include/OpenGLLib.h include/ftconstexpr/ConstexprMath.hpp ../shared/IUI.hpp include/AngledSnakePoints.class.hpp include/ftconstexpr/Vertex.class.hpp include/ftconstexpr/Vertex.class.tpp include/ftconstexpr/Array.class.hpp include/ftconstexpr/Array.class.tpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp ../shared/IGame.hpp ../shared/ISnake.hpp ../shared/IBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Window.draw.o: srcs/Window.draw.cpp include/Window.class.hpp ../shared/nibbler.h include/OpenGLLib.h include/ftconstexpr/ConstexprMath.hpp ../shared/IUI.hpp include/AngledSnakePoints.class.hpp include/ftconstexpr/Vertex.class.hpp include/ftconstexpr/Vertex.class.tpp include/ftconstexpr/Array.class.hpp include/ftconstexpr/Array.class.tpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp ../shared/IGame.hpp ../shared/ISnake.hpp ../shared/IBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/init.o: srcs/init.cpp include/Window.class.hpp ../shared/nibbler.h include/OpenGLLib.h include/ftconstexpr/ConstexprMath.hpp ../shared/IUI.hpp include/AngledSnakePoints.class.hpp include/ftconstexpr/Vertex.class.hpp include/ftconstexpr/Vertex.class.tpp include/ftconstexpr/Array.class.hpp include/ftconstexpr/Array.class.tpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp ../shared/IGame.hpp ../shared/ISnake.hpp ../shared/IBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re

make: fclean
	@python makemake.py
.PHONY: make
