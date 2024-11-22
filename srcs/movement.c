/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:35:37 by jarumuga          #+#    #+#             */
/*   Updated: 2024/08/21 14:47:30 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// check if the move is valid
	// not walking into a wall
	// not walking into an exit without collecting all coins
static int	is_valid_move(t_data *data, int new_x, int new_y)
{
	if (data->map.map[new_y][new_x] == '1')
		return (0);
	if (data->map.map[new_y][new_x] == 'E' && data->map.coin_count != 0)
		return (0);
	return (1);
}

// move the player
static void	move_player(t_data *data, int new_x, int new_y)
{
	if (data->map.map != NULL && is_valid_move(data, new_x, new_y))
	{
		if (data->map.map[new_y][new_x] == 'C')
			data->map.coin_count--;
		data->map.map[data->map.player_y][data->map.player_x] = '0';
		data->map.player_x = new_x;
		data->map.player_y = new_y;
		data->map.map[new_y][new_x] = 'P';
		data->move++;
		ft_printf("Moves: %d\n", data->move);
	}
}

// set player position
void	set_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map[y][x] == 'P')
			{
				data->map.player_x = x;
				data->map.player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_printf("Player position not found\n");
}

// set exit position
void	set_exit_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map[y][x] == 'E')
			{
				data->map.exit_x = x;
				data->map.exit_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

// handle each keypress (WASD and ESC)
int	handle_keypress(int keycode, t_data *data)
{
	if (data->map.map == NULL)
		return (ft_printf("Map is not initialized\n"), 1);
	set_player_position(data);
	if (keycode == XK_w || keycode == XK_W)
		move_player(data, data->map.player_x, data->map.player_y - 1);
	else if (keycode == XK_s || keycode == XK_S)
		move_player(data, data->map.player_x, data->map.player_y + 1);
	else if (keycode == XK_a || keycode == XK_A)
		move_player(data, data->map.player_x - 1, data->map.player_y);
	else if (keycode == XK_d || keycode == XK_D)
		move_player(data, data->map.player_x + 1, data->map.player_y);
	else if (keycode == XK_Escape)
		close_window(data);
	if (check_win(data))
		close_window(data);
	render_map(data);
	return (0);
}
