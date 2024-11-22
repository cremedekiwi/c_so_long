/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:30:28 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/26 11:07:27 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# define TILE_SIZE 42

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**map;
	char	**fill;
	int		width;
	int		height;
	int		has_wall;
	int		has_floor;
	int		has_player;
	int		has_coin;
	int		has_exit;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		coin_count;
	int		v_i;
	int		v_coins;
	int		v_exit;
	char	c;
}	t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*coin;
	void	*exit;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*buffer;
	int		move;
	t_map	map;
	t_point	pt;
	t_img	img;
}	t_data;

// check_map.c
int		check_char(t_data *data);
int		check_double(t_data *data);

// check_map2.c
int		check_rectangle(t_data *data);
int		check_border(t_data *data);
void	count_coins(t_data *data);

// cleanup.c
void	free_map(t_map *map);
void	cleanup(t_data *data);
int		close_window(t_data *data);
int		key_escape(int keycode, t_data *data);

// create_map.c
int		parse_map(t_data *data);
int		load_images(t_data *data);
void	render_map(t_data *data);

// flood_fill.c
int		check_valid_path(t_data *data);

// main.c
int		check_win(t_data *data);

// movement.c
void	set_player_position(t_data *data);
void	set_exit_position(t_data *data);
int		handle_keypress(int keycode, t_data *data);

// read.c
char	*read_map(char *file_path);

// utils.c
void	init_data(t_data *data);
void	put_image(t_data *data, void *image);
int		init_mlx(t_data *data);

#endif
