/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:11:41 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/23 08:55:52 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// check if all coins are collected and player is on exit
int	check_win(t_data *data)
{
	set_player_position(data);
	set_exit_position(data);
	if (data->map.coin_count == 0 && data->map.player_x == data->map.exit_x \
	&& data->map.player_y == data->map.exit_y)
		return (ft_printf("Congrats, you find the exit :)\n"), 1);
	return (0);
}

// init_data(&data) : initializes the data with default values to 0
// read_map("./maps/map1.ber") : reads the map file
// parse_map(buffer) : parse the map
// init_mlx(&data) : initializes MLX
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		{
			init_data(&data);
			data.buffer = read_map(argv[1]);
			if (!data.buffer)
				return (cleanup(&data), 1);
			if (!parse_map(&data))
				return (cleanup(&data), 1);
			if (init_mlx(&data) != 0)
				return (cleanup(&data), 1);
			cleanup(&data);
		}
		else
			return (ft_putstr_fd("Error\n'.ber' file only\n", 2), 1);
	}
	else
		return (ft_putstr_fd("Error\nSyntax is ./so_long 'map.ber'\n", 2), 1);
	return (0);
}
