/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/16 17:47:28 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_v(int keycode, t_data *data)
{
	double	next_x;
	double	next_y;

	printf("adresse data = %p\n", data);
	printf("adresse map  = %p\n", data->map);
	if (keycode == KEY_UP || keycode == KEY_H)
	{
		next_x = data->map->player_x + cos(data->map->player_dir) * SPEED;
		next_y = data->map->player_y + sin(data->map->player_dir) * SPEED;
	}
	else
	{
		next_x = data->map->player_x - cos(data->map->player_dir) * SPEED;
		next_y = data->map->player_y - sin(data->map->player_dir) * SPEED;
	}
	if ((check_collision(data, next_x, next_y)) == 0)
	{
		data->map->player_x = next_x;
		data->map->player_y = next_y;
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr,
			0, 0);
	}
}

void	move_h(int keycode, t_data *data)
{
	double	next_x;
	double	next_y;

	if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		next_x = data->map->player_x - cos(data->map->player_dir - PI / 2)
			* SPEED;
		next_y = data->map->player_y + sin(data->map->player_dir - PI / 2)
			* SPEED;
	}
	else
	{
		next_x = data->map->player_x + cos(data->map->player_dir - PI / 2)
			* SPEED;
		next_y = data->map->player_y - sin(data->map->player_dir - PI / 2)
			* SPEED;
	}
	if ((check_collision(data, next_x, next_y)) == 0)
	{
		data->map->player_x = next_x;
		data->map->player_y = next_y;
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr,
			0, 0);
	}
}

int	check_collision(t_data *data, double n_x, double n_y)
{
	int	check_x;
	int	check_y;
	int	i;

	data->moves.dx[0] = TILE_P;
	data->moves.dx[1] = TILE_P;
	data->moves.dx[2] = -TILE_P;
	data->moves.dx[3] = -TILE_P;
	data->moves.dy[0] = TILE_P;
	data->moves.dy[1] = -TILE_P;
	data->moves.dy[2] = TILE_P;
	data->moves.dy[3] = -TILE_P;
	i = 0;
	while (i < 4)
	{
		check_x = (n_x + data->moves.dx[i]) / TILE;
		check_y = (n_y + data->moves.dy[i]) / TILE;
		if (check_x < 0 || check_x > data->map->width || check_y < 0
			|| check_y > data->map->height)
			return (1);
		if (data->map->grid[check_y][check_x] == '1')
			return (1);
		i++;
	}
	return (0);
}
