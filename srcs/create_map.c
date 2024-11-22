/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:39:48 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/26 10:57:55 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// calculate the dimension of my map (height and width)
	// if a newline is found, height++
	// calculate the width of my map only on the first row
static void	calc_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map.height = 0;
	data->map.width = 0;
	while (data->buffer[i])
	{
		if (data->buffer[i] == '\n')
			data->map.height++;
		else if (data->map.height == 0)
			data->map.width++;
		i++;
	}
}

// loop through the buffer to fill the map
// find the newline and calculate line length
// malloc for the map row and copy the line
// move to the next line
// terminate the map and return (1)
static int	fill_map(t_data *data)
{
	char	*line_start;
	char	*newline_pos;
	int		row;
	size_t	line_length;

	line_start = data->buffer;
	row = -1;
	while (line_start && ++row < data->map.height)
	{
		newline_pos = ft_strchr(line_start, '\n');
		if (newline_pos)
			line_length = newline_pos - line_start;
		else
			line_length = ft_strlen(line_start);
		data->map.map[row] = malloc(line_length + 1);
		if (!data->map.map[row])
			return (0);
		ft_strlcpy(data->map.map[row], line_start, line_length + 1);
		if (newline_pos)
			line_start = newline_pos + 1;
		else
			line_start = NULL;
	}
	data->map.map[row] = NULL;
	return (1);
}

// init the map dimensions, malloc the map and then fills the map with data
int	parse_map(t_data *data)
{
	data->map.height = 0;
	data->map.width = 0;
	calc_map_size(data);
	if (data->map.height <= 0 || data->map.width <= 0)
		return (0);
	data->map.map = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map)
		return (0);
	if (!fill_map(data))
	{
		free_map(&data->map);
		return (0);
	}
	return (1);
}

// load images with mlx_xpm_file_to_image
int	load_images(t_data *data)
{
	data->img.wall = mlx_xpm_file_to_image(data->mlx, \
	"./textures/wall.xpm", &data->img.width, &data->img.height);
	data->img.floor = mlx_xpm_file_to_image(data->mlx, \
	"./textures/floor.xpm", &data->img.width, &data->img.height);
	data->img.player = mlx_xpm_file_to_image(data->mlx, \
	"./textures/player.xpm", &data->img.width, &data->img.height);
	data->img.coin = mlx_xpm_file_to_image(data->mlx, \
	"./textures/coin.xpm", &data->img.width, &data->img.height);
	data->img.exit = mlx_xpm_file_to_image(data->mlx, \
	"./textures/exit.xpm", &data->img.width, &data->img.height);
	if (!data->img.wall || !data->img.floor || !data->img.player \
	|| !data->img.coin || !data->img.exit)
	{
		ft_putstr_fd("Error\nFailed to load texture\n", 2);
		return (1);
	}
	return (0);
}

// replace each char of my map to the right image
void	render_map(t_data *data)
{
	count_coins(data);
	data->pt.y = -1;
	while (++data->pt.y < data->map.height)
	{
		data->pt.x = -1;
		while (++data->pt.x < data->map.width)
		{
			data->map.c = data->map.map[data->pt.y][data->pt.x];
			if (data->map.c == '1')
				put_image(data, data->img.wall);
			else if (data->map.c == '0')
				put_image(data, data->img.floor);
			else if (data->map.c == 'P')
				put_image(data, data->img.player);
			else if (data->map.c == 'C')
				put_image(data, data->img.coin);
			else if (data->map.c == 'E')
				put_image(data, data->img.exit);
		}
	}
}
