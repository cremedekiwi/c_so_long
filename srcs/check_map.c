/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:46:54 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/26 11:07:38 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// update flags for each char
static int	map_flags(t_data *data)
{
	data->map.c = data->map.map[data->pt.y][data->pt.x];
	if (data->map.c == '1')
		data->map.has_wall = 1;
	else if (data->map.c == '0')
		data->map.has_floor = 1;
	else if (data->map.c == 'P')
		data->map.has_player = 1;
	else if (data->map.c == 'C')
		data->map.has_coin = 1;
	else if (data->map.c == 'E')
		data->map.has_exit = 1;
	else
		return (ft_putstr_fd("Error\nInvalid char\n", 2), 0);
	return (1);
}

// check if i have at least one of each char
int	check_char(t_data *data)
{
	data->pt.y = -1;
	while (++data->pt.y < data->map.height)
	{
		data->pt.x = -1;
		while (++data->pt.x < data->map.width)
		{
			if (!map_flags(data))
				return (0);
		}
	}
	if (data->map.has_wall && data->map.has_floor >= 0 && data->map.has_player \
	&& data->map.has_coin && data->map.has_exit)
		return (1);
	else
		return (ft_putstr_fd("Error\nMap must contain all req. char\n", 2), 0);
}

// check if player and exit are in double
int	check_double(t_data *data)
{
	data->pt.y = -1;
	while (++data->pt.y < data->map.height)
	{
		data->pt.x = -1;
		while (++data->pt.x < data->map.width)
		{
			data->map.c = data->map.map[data->pt.y][data->pt.x];
			if (data->map.c == 'P')
				data->map.has_player++;
			else if (data->map.c == 'E')
				data->map.has_exit++;
		}
	}
	if (data->map.has_player <= 1 && data->map.has_exit <= 1)
		return (1);
	else
		return (ft_putstr_fd("Error\nDuplicate player or exit\n", 2), 0);
}
