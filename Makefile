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
LIBS := lib/OpenGL lib/Ncurses

# Number of threads
THREADS := 2

# Cpp compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# Clang++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2 -std=c++14

# Linking flags
LD_FLAGS := 

# Clang++ include flags
CPP_HEADS := -Iinclude -Icommon

#
# Internal
#

O_FILES := o/srcs/Snake.o \
	o/srcs/ABlock.o \
	o/srcs/main.o \
	o/srcs/GrowBonus.o \
	o/srcs/Game.o \
	o/srcs/Event.o

MSG_0 := printf '\033[0;32m%-21.21s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-21.21s\033[0;0m\n'

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && echo || $(MSG_1) $@

o/srcs/Snake.o: srcs/Snake.cpp include/Snake.hpp include/Game.hpp include/ABlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/ABlock.o: srcs/ABlock.cpp include/ABlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/main.o: srcs/main.cpp common/nibbler.h common/IUI.hpp include/Game.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/GrowBonus.o: srcs/GrowBonus.cpp include/GrowBonus.hpp include/Snake.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Game.o: srcs/Game.cpp common/nibbler.h include/Game.hpp common/IUI.hpp include/Event.hpp include/GrowBonus.hpp common/IBlock.hpp include/ABlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Event.o: srcs/Event.cpp common/nibbler.h include/Event.hpp include/Game.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

include/ABlock.hpp: common/nibbler.h common/IBlock.hpp

include/Game.hpp: common/nibbler.h common/IGame.hpp include/Snake.hpp

include/GrowBonus.hpp: common/nibbler.h include/ABlock.hpp

include/Snake.hpp: common/nibbler.h common/ISnake.hpp

common/IGame.hpp: common/nibbler.h

common/ISnake.hpp: common/nibbler.h

common/IUI.hpp: common/nibbler.h

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
