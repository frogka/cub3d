/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/15 18:58:09 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_v(int keycode, t_data *data)
{
	double	next_x;
	double	next_y;
	// int		grid_x;
	// int		grid_y;

	printf("adresse data = %p\n", data);
	printf("adresse map  = %p\n", data->map);
	if (keycode == KEY_UP)
	{
		next_x = data->map->player_x + cos(data->map->player_dir) * speed;
		next_y = data->map->player_y + sin(data->map->player_dir) * speed;
	}
	else
	{
		next_x = data->map->player_x - cos(data->map->player_dir) * speed;
		next_y = data->map->player_y - sin(data->map->player_dir) * speed;
	}
	// grid_x = (int)(next_x / TILE); // ajout pour eviter colision murs
	// grid_y = (int)(next_y / TILE); // ajout pour eviter colision murs
	// printf("grid_x = %d, grid_y = %d, height = %d, width = %d\n", grid_x,
	// 	grid_y, data->map->height, data->map->width);
	// gere la distance aux murs
	if ((check_collision(data, next_x, next_y)) == 0)
	{
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr,
			0, 0);
	}
}

void	move_h(int keycode, t_data *data)
{
	double	next_x;
	double	next_y;
	// int		grid_x;
	// int		grid_y;

	if (keycode == KEY_RIGHT)
	{
		next_x = data->map->player_x - cos(data->map->player_dir - PI / 2)
			* speed;
		next_y = data->map->player_y + sin(data->map->player_dir - PI / 2)
			* speed;
	}
	else
	{
		next_x = data->map->player_x + cos(data->map->player_dir - PI / 2)
			* speed;
		next_y = data->map->player_y - sin(data->map->player_dir - PI / 2)
			* speed;
	}
	// grid_x = (int)(next_x / TILE); // ajout pour eviter colision murs
	// grid_y = (int)(next_y / TILE); // ajout pour eviter colision murs
	if ((check_collision(data, next_x, next_y)) == 0)
	{
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr,
			0, 0);
	}
}

int	check_collision(t_data *data, double n_x, double n_y)
{
	double top;
	double bottom;
	double left;
	double right;
	int top_b;
	int bottom_b;
	int left_b;
	int right_b;

	top = n_y - RAYON;
	bottom = n_y + RAYON;
	left = n_x - RAYON;
	right = n_x + RAYON;

	top_b = (int)(top / TILE);
	bottom_b = (int)(bottom / TILE);
	left_b = (int)(left / TILE);
	right_b = (int)(right / TILE);

	if (data->map->grid[top_b][left_b] != '1'
		&& data->map->grid[top_b][right_b] != '1'
		&& data->map->grid[bottom_b][left_b] != '1'
		&& data->map->grid[bottom_b][right_b] != '1')
	{
		data->map->player_x = n_x;
		data->map->player_y = n_y;
		return (0);
	}
	return (1);

	// if (keycode == KEY_UP || keycode == KEY_DOWN)
	// {
	// 	//x = x;
	// 	if (keycode == KEY_UP)
	// 		y += (int)(top / TILE);
	// 	else
	// 		y += (int)(bottom / TILE);
	// }
	// else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	// {
	// 	//y = y;
	// 	if (keycode == KEY_LEFT)
	// 		x += (int)(left / TILE);
	// 	else
	// 		x += (int)(right / TILE);
	// }
	// if (data->map->grid[y][x] != '1')
	// {
	// 	data->map->player_x = x;
	// 	data->map->player_y = y;
	// 	draw_map(data->map, data);
	// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr,
	//		0,0);
	// }

	// if (keycode == KEY_UP)
	// {
	// 	y = (int)(top / TILE);
	// 	x = x;
	// 	if (data->map->grid[y][x] != '1')
	// 	{
	// 		data->map->player_x = x;
	// 		data->map->player_y = y;
	// 	}
	// }
	// if (keycode == KEY_DOWN)
	// {
	// 	y = (int)(bottom / TILE);
	// }
	// if (keycode == KEY_LEFT)
	// {
	// 	x = (int)(left / TILE);
	// }
	// if (keycode == KEY_RIGHT)
	// {
	// 	x = (int)(right / TILE);
	// }
}