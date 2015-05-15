#
# nibbler
#
# Makefile
#

#
# Config
#

# Project name
NAME := nibbler

# Project directories
DIRS := srcs include common

# Obj directory
O_DIR := o

# Makefiles to call
LIBS := lib/OpenGL lib/Ncurses lib/Sfml

# Number of threads
THREADS := 2

# Cpp compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# Clang++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2 -std=c++14 -g

# Linking flags
LD_FLAGS := 

# Clang++ include flags
CPP_HEADS := -Iinclude -Icommon

#
# Internal
#

O_FILES := o/srcs/Snake.o \
	o/srcs/ABlock.o \
	o/srcs/WallBlock.o \
	o/srcs/WallSpawnBlock.o \
	o/srcs/main.o \
	o/srcs/GrowBlock.o \
	o/srcs/Game.o \
	o/srcs/Event.o

MSG_0 := printf '\033[0;32m%-23.23s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-23.23s\033[0;0m\n'

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && echo || $(MSG_1) $@

o/srcs/Snake.o: srcs/Snake.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/ABlock.o: srcs/ABlock.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/WallBlock.o: srcs/WallBlock.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/WallSpawnBlock.o: srcs/WallSpawnBlock.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/main.o: srcs/main.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/GrowBlock.o: srcs/GrowBlock.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp include/GrowBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Game.o: srcs/Game.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp include/GrowBlock.hpp common/IUI.hpp include/Event.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Event.o: srcs/Event.cpp include/Snake.hpp common/nibbler.h common/ISnake.hpp include/Game.hpp common/IGame.hpp include/ABlock.hpp common/IBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp include/GrowBlock.hpp common/IUI.hpp include/Event.hpp
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
