/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/07 17:52:31 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keycode, t_map *map, t_data *data)
{
	if (keycode == KEY_LEFT)
		moove_left(map);
	if (keycode == KEY_RIGHT)
		moove_right(map);
	if (keycode == KEY_UP)
		moove_up(map, data);
	if (keycode == KEY_DOWN)
		moove_down(map, data);
	if (keycode == KEY_ESC)
		destroy(map);
	//iter_reset(keycode, map);
	//change_iter(keycode, map);
	return (0);
}

void moove_up(t_map *map, t_data *data)
{
	double next_x;
	double next_y;
	int grid_x;
	int grid_y;

	next_x = map->player_x + cos(map->player_dir) * speed;
	next_y = map->player_y + sin(map->player_dir) * speed;
	grid_x = (int)next_x / TILE;
	grid_y = (int)next_y / TILE;

	if (map->grid[grid_y][grid_x] != 1)
	{
		map->player_x = next_x;
		map->player_y = next_y;
		draw_map(map, data, map->player_x, map->player_y);
	}
}
void moove_down(t_map *map, t_data *data)
{
	double next_x;
	double next_y;
	int grid_x;
	int grid_y;

	next_x = map->player_x - cos(map->player_dir) * speed;
	next_y = map->player_y - sin(map->player_dir) * speed;
	grid_x = (int)next_x / TILE;
	grid_y = (int)next_y / TILE;

	if (map->grid[grid_y][grid_x] != 1)
	{
		map->player_x = next_x;
		map->player_y = next_y;
		draw_map(map, data, map->player_x, map->player_y);
	}
}





void	init_hook(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 02, 1L << 0, handle_input, data);
	//mlx_mouse_hook(data->win_ptr, mouse_hook, data);
}


int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(1);
}