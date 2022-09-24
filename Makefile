# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 13:57:28 by dpalacio          #+#    #+#              #
#    Updated: 2022/09/24 14:24:10 by dpalacio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
FLAGS = -Wall -Wextra -Werror -flto -Ofast

MY_PATH = $(shell pwd)

INCLUDE = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) $(SDL_HEADERS)

LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)include/
LIBFT = $(LIBFT_DIR)libft.a

SDL_DIR = ./SDL/
SDL_HEADERS = \
	-I$(SDL_DIR)SDL2.framework/Versions/A/Headers \
	-I$(SDL_DIR)SDL2_ttf.framework/Versions/A/Headers \

LIBS = -L$(LIBFT_DIR) -lft

FRAMEWORKS = -F$(SDL_DIR) \
				-rpath $(SDL_DIR) \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf

HEADERS_LIST = \
	wolf3d.h
HEADERS_DIR = ./include/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = ./src/
SRC_LIST = \
	main.c \
	init.c \
	read_map.c \
	render.c \
	wall_casting.c \
	floor_casting.c \
	draw.c \
	controls.c \
	my_sdl.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

SDL_EXISTS=$(shell [ -e  ] && echo 1 || echo 0 )

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) $(FRAMEWORKS) $(INCLUDE) $(OBJ) -o $(NAME)
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

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(YELLOW)Removed objects directory$(RESET)"
	@echo "$(NAME): $(YELLOW)Removed object files$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@echo "$(NAME): $(YELLOW)Libft was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(YELLOW)Wolf3d executable was deleted$(RESET)"

re: fclean all
