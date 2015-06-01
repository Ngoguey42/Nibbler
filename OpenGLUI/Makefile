#
# OpenGLUI.so
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
LD_FLAGS := -fPIC -shared -L ~/.brew/lib -lglfw3 -lftgl -lGLEW -framework OpenGL

# Clang++ include flags
CPP_HEADS := -Iinclude -I../shared -I../extern -I ~/.brew/include -I ~/.brew/Cellar/freetype/2.5.5/include/freetype2

NICE_OUTPUT := 0

#
# Internal
#

O_FILES := o/srcs/draw_items.o \
	o/srcs/OpenGLUI.class.o \
	o/srcs/draw_texts.o \
	o/srcs/draw_snake.o \
	o/srcs/draw_ground.o \
	o/srcs/init.o \
	o/srcs/draw_background.o

MSG_0 := printf '\033[0;32m%s\033[0;0m\n'
MSG_1 := printf '\033[0;31m%s\033[0;0m\n'
MSG_END := true

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/srcs/draw_items.o: srcs/draw_items.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/OpenGLUI.class.o: srcs/OpenGLUI.class.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/draw_texts.o: srcs/draw_texts.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/draw_snake.o: srcs/draw_snake.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/draw_ground.o: srcs/draw_ground.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/init.o: srcs/init.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/draw_background.o: srcs/draw_background.cpp include/OpenGLUI.class.hpp ../shared/nibbler.h ../shared/IBlock.hpp ../shared/IUI.hpp ../shared/IGame.hpp ../shared/ISnake.hpp include/OpenGLLib.h include/AngledSnakePoints.class.hpp include/CornerPoints.class.hpp include/CornerPoints.class.tpp include/AngledSnakePoints.class.tpp
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
