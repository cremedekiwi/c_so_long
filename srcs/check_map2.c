/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:59:47 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/26 11:06:19 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// check if my map is a rectangle
// data->pt.y < data->map.height : check one row at a time
	// check the width of my row with the width of my map
int	check_rectangle(t_data *data)
{
	data->pt.y = 0;
	while (data->pt.y < data->map.height)
	{
		if (ft_strlen(data->map.map[data->pt.y]) == 0)
		{
			ft_putstr_fd("Error\nYou have at least one empty line\n", 2);
			return (0);
		}
		if (ft_strlen(data->map.map[data->pt.y]) != data->map.width)
		{
			ft_putstr_fd("Error\nMap is not a rectangle\n", 2);
			return (0);
		}
		data->pt.y++;
	}
	return (1);
}

// check if surrounded by walls (1)
// check top and bottom rows
// check first and last columns
int	check_border(t_data *data)
{
	data->pt.x = 0;
	while (data->pt.x < data->map.width)
	{
		if (data->map.map[0][data->pt.x] != '1' || \
		data->map.map[data->map.height - 1][data->pt.x] != '1')
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (0);
		}
		data->pt.x++;
	}
	data->pt.y = 0;
	while (data->pt.y < data->map.height)
	{
		if (data->map.map[data->pt.y][0] != '1' \
		|| data->map.map[data->pt.y][data->map.width - 1] != '1')
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			return (0);
		}
		data->pt.y++;
	}
	return (1);
}

// count coins
void	count_coins(t_data *data)
{
	data->map.coin_count = 0;
	data->pt.y = -1;
	while (++data->pt.y < data->map.height)
	{
		data->pt.x = -1;
		while (++data->pt.x < data->map.width)
		{
			data->map.c = data->map.map[data->pt.y][data->pt.x];
			if (data->map.c == 'C')
				data->map.coin_count++;
		}
	}
}
