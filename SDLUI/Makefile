#
# SDLUI.so
#
# Makefile
#

#
# Config
#

# Project name
NAME := SDLUI.so

# Project directories
DIRS := srcs include ../shared

# Obj directory
O_DIR := o

# Number of threads
THREADS := 1

# Cpp compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# Clang++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2 -std=c++14

# Linking flags
LD_FLAGS := -fPIC -shared -L ~/.brew/lib -lSDL2 -lSDL2_ttf

# Clang++ include flags
CPP_HEADS := -I../shared -Iinclude -I ~/.brew/include

MAKEMAKE_TMP := tmp_makemake.py

#
# Internal
#

O_FILES := o/srcs/SDLUI.o \
	o/srcs/init.o

MSG_0 := printf '\033[0;32m%-14.14s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-14.14s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/srcs/SDLUI.o: srcs/SDLUI.cpp include/SDLUI.hpp ../shared/nibbler.h ../shared/IUI.hpp ../shared/IBlock.hpp ../shared/IGame.hpp ../shared/ISnake.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/init.o: srcs/init.cpp include/SDLUI.hpp ../shared/nibbler.h ../shared/IUI.hpp ../shared/IBlock.hpp ../shared/IGame.hpp ../shared/ISnake.hpp
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
