# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2016/06/28 17:38:47 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

# Dir vars

SRCDIR = src

INCLUDESDIR = includes

LIBDIR = libft

# Files vars

MAIN = main.c

CFILES = ft_event.c ft_init_mlx.c ft_run.c \
			ft_bmp.c ft_fractals.c ft_sub_event.c \

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

HFILES = fractol.h

HEADERS = $(patsubst %, $(INCLUDESDIR)/%, $(HFILES))

# COMPILATION

ERRORFLAGS = -Wall -Werror -Wextra -W -march=native -Ofast

INCLUDEFLAGS = -I $(INCLUDESDIR)/ -I $(LIBDIR)/includes/ -I./minilibx

# MLX = -L./minilibx -lmlx -L/lib -lXext -lx11
MLX = -L./minilibx -lmlx -framework OpenGL -framework AppKit

LIBFLAGS = -L $(LIBDIR)/ -lft

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS)

CC = gcc

# Git vars

TOGIT =	$(SRC) \
		$(HEADERS) \
		$(MAIN) \
		Makefile \
		auteur \
		$(LIBDIR) \
		minilibx

# Rules

all: $(NAME)

$(NAME): $(OBJ)
			@make -j -C $(LIBDIR)/
			@$(CC) $(FLAGS) $(OBJ) $(LIBFLAGS) $(MLX) -o $(NAME)

re: fclean all

clean:
			@rm -f $(OBJ)
			@make -C $(LIBDIR)/ clean

fclean: clean
			@rm -f $(NAME)
			@make -j -C $(LIBDIR)/ fclean

relib:
		@make -j -C $(LIBDIR)/ re

%.o: %.c
			@$(CC) -o $@ -c $< $(FLAGS)

git:
		git add $(TOGIT)
		git commit -m 'auto update'
		git push
