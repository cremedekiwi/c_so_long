# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 15:01:43 by jarumuga          #+#    #+#              #
#    Updated: 2024/08/26 11:06:36 by jarumuga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
FLAGS = -Wall -Wextra -Werror -g
LLIB = -L./libft -lft
LMLX = -L./minilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11
INCLUDES = -I./includes -I./libft/includes -I./minilibx-linux
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS =	$(SRCS_DIR)/check_map.c \
		$(SRCS_DIR)/check_map2.c \
		$(SRCS_DIR)/cleanup.c \
		$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/create_map.c \
		$(SRCS_DIR)/flood_fill.c \
		$(SRCS_DIR)/movement.c \
		$(SRCS_DIR)/read.c \
		$(SRCS_DIR)/utils.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a minilibx-linux/libmlx.a
	$(CC) -o $(NAME) $(OBJS) $(LLIB) $(LMLX)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	$(MAKE) -C libft

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re
