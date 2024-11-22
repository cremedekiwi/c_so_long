/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:01:16 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/23 17:11:31 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// flood fill algorithm to check if there is a valid path
// check if outside the map
// check if the current cell is a wall or already visited
// the current cell is marked as visited
// if the current cell is a coin, increment the coin count
// if the current cell is an exit, mark the exit as visited
// recursively call the function for the adjacent cells
static void	flood_fill(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return ;
	if (data->map.map[y][x] == '1' || data->map.fill[y][x] == 'V')
		return ;
	if (data->map.map[y][x] == 'E' && data->map.v_coins < data->map.coin_count)
		return ;
	data->map.fill[y][x] = 'V';
	if (data->map.map[y][x] == 'C')
		data->map.v_coins++;
	if (data->map.map[y][x] == 'E')
		data->map.v_exit = 1;
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}

static void	free_map_fill(t_data *data)
{
	int	i;

	if (data->map.fill)
	{
		i = 0;
		while (i < data->map.height)
		{
			if (data->map.fill[i])
				free(data->map.fill[i]);
			i++;
		}
		free(data->map.fill);
	}
}

// check if there is a valid path
// set the player position
// count the coins
// allocate memory for the visited map
// initialize every cell to '0'
// call the flood fill algorithm
// it explores the map and marks the visited cells
// count the coins and mark the exit as visited
// free the memory allocated for the visited map
// checks if all coins are collected and exit is visited
int	check_valid_path(t_data *data)
{
	set_player_position(data);
	count_coins(data);
	data->map.fill = malloc(data->map.height * sizeof(char *));
	if (!data->map.fill)
		return (0);
	data->map.v_i = -1;
	while (++data->map.v_i < data->map.height)
	{
		data->map.fill[data->map.v_i] = malloc(data->map.width * sizeof(char));
		if (!data->map.fill[data->map.v_i])
			return (free_map_fill(data), 0);
	}
	data->pt.y = -1;
	while (++data->pt.y < data->map.height)
	{
		data->pt.x = -1;
		while (++data->pt.x < data->map.width)
			data->map.fill[data->pt.y][data->pt.x] = '0';
	}
	flood_fill(data, data->map.player_x, data->map.player_y);
	free_map_fill(data);
	if ((data->map.v_coins == data->map.coin_count) && data->map.v_exit)
		return (1);
	ft_putstr_fd("Error\nNo valid path\n", 2);
	return (0);
}
