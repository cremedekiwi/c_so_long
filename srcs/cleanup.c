/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:17:48 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/22 17:58:39 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// destroy each image when you exit
static void	destroy_img(t_data *data)
{
	if (data->img.wall)
	{
		mlx_destroy_image(data->mlx, data->img.wall);
		data->img.wall = NULL;
	}
	if (data->img.floor)
	{
		mlx_destroy_image(data->mlx, data->img.floor);
		data->img.floor = NULL;
	}
	if (data->img.player)
	{
		mlx_destroy_image(data->mlx, data->img.player);
		data->img.player = NULL;
	}
	if (data->img.coin)
	{
		mlx_destroy_image(data->mlx, data->img.coin);
		data->img.coin = NULL;
	}
	if (data->img.exit)
	{
		mlx_destroy_image(data->mlx, data->img.exit);
		data->img.exit = NULL;
	}
}

// free each coordinate, then the map
void	free_map(t_map *map)
{
	int	i;

	if (map && map->map)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->map[i])
			{
				free(map->map[i]);
				map->map[i] = NULL;
			}
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
}

// free any allocated resources
// buffer, map, image, window and display
void	cleanup(t_data *data)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data)
	{
		if (data->map.map)
			free_map(&data->map);
		destroy_img(data);
		if (data->win)
		{
			mlx_destroy_window(data->mlx, data->win);
			data->win = NULL;
		}
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			data->mlx = NULL;
		}
	}
}

// call cleanup to destroy window
int	close_window(t_data *data)
{
	cleanup(data);
	exit(0);
}

// when i press esc, call close window
int	key_escape(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	return (0);
}
