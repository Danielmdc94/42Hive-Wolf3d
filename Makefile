# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 13:57:28 by dpalacio          #+#    #+#              #
#    Updated: 2022/06/17 13:03:01 by dpalacio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
FLAGS = -Wall -Wextra -Werror -flto

MY_PATH = $(shell pwd)

INCLUDE = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)include/
LIBFT = $(LIBFT_DIR)libft.a

SDL_DIR = ./sdl/
SDL_HEADERS = $(SDL_DIR)include/SDL2 -D_THREAD_SAFE
SDL = $(SDL_DIR)build/build/.libs/

LIBS = -L$(LIBFT_DIR) -lft  -L$(SDL) -lSDL2

HEADERS_LIST = \
	wolf3d.h
HEADERS_DIR = ./include/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = ./src/
SRC_LIST = \
	main.c \
	read_map.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

SDL_EXISTS=$(shell [ -e  ] && echo 1 || echo 0 )

.PHONY: all clean fclean re sdl

all: $(LIBFT) sdl_install $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) $(INCLUDE) $(OBJ) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)Created object files.$(RESET)"
	@echo "$(NAME): $(GREEN)Created Wolf3d executable.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GREEN)Created obj/ directory.$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDE) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Compiling Libft...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

sdl_install:
	@if [ -d "$(SDL_DIR)build/" ];\
	then\
		echo "$(NAME): $(YELLOW)SDL2 already exists.$(RESET)";\
	else\
		mkdir -p $(SDL_DIR)build/;\
		echo "$(NAME): $(GREEN)Configuring SDL2...$(RESET)";\
		cd $(SDL_DIR)build/; ../configure --prefix $(MYPATH)/sdl/build;\
		cd $(MY_PATH);\
		bash sdl_path.sh;\
		echo "$(NAME): $(GREEN)Installing SDL2...$(RESET)";\
		$(MAKE) -sC $(SDL_DIR)build/ install;\
		echo "$(NAME): $(GREEN)SDL2  was installed.$(RESET)";\
	fi;

sdl_uninstall:
	@rm -fr $(SDL_DIR)build/
	@echo "$(NAME): $(YELLOW)SDL2 was uninstalled.$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(YELLOW)Removed objects directory$(RESET)"
	@echo "$(NAME): $(YELLOW)Removed object files$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(YELLOW)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(YELLOW)$(NAME) was deleted$(RESET)"
	@rm -fr $(SDL_DIR)build/
	@echo "$(NAME): $(YELLOW)SDL2 was uninstalled.$(RESET)"

re: fclean all
