#
# ../SfmlUI.so
#
# Makefile
#

#
# Config
#

# Project name
NAME := ../SfmlUI.so

# Project directories
DIRS := srcs include ../../common

# Obj directory
O_DIR := o

# Number of threads
THREADS := 4

# Cpp compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# Clang++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2 -std=c++14

# Linking flags
LD_FLAGS := -fPIC -shared -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Clang++ include flags
CPP_HEADS := -Iinclude -I../../common -I ~/.brew/include

#
# Internal
#

O_FILES := o/srcs/SfmlUI.o \
	o/srcs/init.o

MSG_0 := printf '\033[0;32m%-15.15s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-15.15s\033[0;0m\n'

.SILENT:

all: $(LIBS)
	@make -j$(THREADS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && echo || $(MSG_1) $@

o/srcs/SfmlUI.o: srcs/SfmlUI.cpp include/SfmlUI.hpp ../../common/nibbler.h ../../common/IBlock.hpp ../../common/IUI.hpp ../../common/IGame.hpp ../../common/ISnake.hpp
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/srcs/init.o: srcs/init.cpp include/SfmlUI.hpp ../../common/nibbler.h ../../common/IBlock.hpp ../../common/IUI.hpp ../../common/IGame.hpp ../../common/ISnake.hpp
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
