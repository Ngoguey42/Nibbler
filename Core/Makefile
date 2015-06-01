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
DIRS := srcs include ../shared

# Obj directory
O_DIR := o

# Makefiles to call
LIBS := 

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
CPP_HEADS := -Iinclude -I../shared

MAKEMAKE_TMP := tmp_makemake.py

#
# Internal
#

O_FILES := o/srcs/Snake.o \
	o/srcs/ABlock.o \
	o/srcs/Game.o \
	o/srcs/WallSpawnBlock.o \
	o/srcs/main.o \
	o/srcs/GrowBlock.o \
	o/srcs/Settings.o \
	o/srcs/BonusBlock.o \
	o/srcs/ft_argv.o \
	o/srcs/Event.o \
	o/srcs/WallBlock.o

MSG_0 := printf '\033[0;32m%-23.23s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-23.23s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/srcs/Snake.o: srcs/Snake.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/ABlock.o: srcs/ABlock.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Game.o: srcs/Game.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/WallSpawnBlock.o: srcs/WallSpawnBlock.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/main.o: srcs/main.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/GrowBlock.o: srcs/GrowBlock.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Settings.o: srcs/Settings.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/BonusBlock.o: srcs/BonusBlock.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/ft_argv.o: srcs/ft_argv.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/Event.o: srcs/Event.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/WallBlock.o: srcs/WallBlock.cpp ../shared/nibbler.h include/Snake.hpp ../shared/ISnake.hpp include/Game.hpp ../shared/IGame.hpp include/Settings.hpp include/ft_argv.h include/ABlock.hpp ../shared/IBlock.hpp ../shared/IAudio.hpp ../shared/IUI.hpp include/Event.hpp include/GrowBlock.hpp include/BonusBlock.hpp include/WallBlock.hpp include/WallSpawnBlock.hpp
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
	@curl -f https://raw.githubusercontent.com/Julow/makemake/master/makemake.py > $(MAKEMAKE_TMP)
	@python $(MAKEMAKE_TMP)
	@rm -f $(MAKEMAKE_TMP)
.PHONY: make
