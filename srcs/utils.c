/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:17:39 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/26 10:59:32 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// initializes the data structure with default values
void	init_data(t_data *data)
{
	if (data == NULL)
		return ;
	ft_bzero(data, sizeof(t_data));
}

// put image to window
void	put_image(t_data *data, void *image)
{
	mlx_put_image_to_window(data->mlx, data->win, image, \
	data->pt.x * TILE_SIZE, data->pt.y * TILE_SIZE);
}

// initializes a window
// the width and height are map.? * the tile length (42)
static int	init_window(t_data *data)
{
	int	win_width;
	int	win_height;
	int	screen_width;
	int	screen_height;

	screen_width = 0;
	screen_height = 0;
	mlx_get_screen_size(data->mlx, &screen_width, &screen_height);
	win_width = data->map.width * TILE_SIZE;
	win_height = data->map.height * TILE_SIZE;
	if (win_width > screen_width || win_height > screen_height)
	{
		ft_putstr_fd("Error\nWindow size is too large\n", 2);
		return (1);
	}
	data->win = mlx_new_window(data->mlx, win_width, win_height, "so_long");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
		return (1);
	}
	return (0);
}

// sets up event hooks
// press esc, close with 'x', and count move
static void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->win, handle_keypress, data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, close_window, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_escape, data);
}

// initializes MLX
// init_window(&data, map) : initializes a graphical window
// load_images(&data) : loads images
// render_map(&data, map) : renders the map to the window
// setup_hooks(&data) : sets up event hooks
// mlx_loop(data.mlx) : keep the window alive and wait for events
int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	if (!check_rectangle(data) || !check_border(data) || \
	!check_double(data) || !check_char(data) || !check_valid_path(data))
		close_window(data);
	if (init_window(data) != 0)
		return (cleanup(data), 1);
	if (load_images(data) != 0)
		return (cleanup(data), 1);
	render_map(data);
	setup_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}
