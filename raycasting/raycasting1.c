/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:52:44 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/21 21:18:46 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rays(t_data *data)
{
	double	rays_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	int		i;

	rays_angle = data->map->player_dir - FOV / 2;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_dir_x = cos(rays_angle);
		ray_dir_y = sin(rays_angle);
		data->ray.ray_angle = rays_angle;
		draw_one_ray(data, ray_dir_x, ray_dir_y, i);
		rays_angle += FOV / NUM_RAYS;
		if (rays_angle < 0)
			rays_angle += 2 * PI;
		if (rays_angle > 2 * PI)
			rays_angle -= 2 * PI;
		i++;
	}
}

void	draw_one_ray(t_data *data, double ray_dx, double ray_dy, int ray_id)
{
	double	pos_x;
	double	pos_y;
	int		x;
	int		y;
	int		step;

	pos_x = data->map->player_x;
	pos_y = data->map->player_y;
	step = 0;
	while (step < 5000)
	{
		pos_x += ray_dx * 1;
		pos_y += ray_dy * 1;
		x = pos_x / TILE;
		y = pos_y / TILE;
		if (x < 0 || x >= data->map->width || y < 0 || y >= data->map->height)
			return ;
		if (data->map->grid[y][x] == '1')
		{
			dist_rays_wall(data, pos_x, pos_y, ray_id);
			return ;
		}
		// else
		// 	my_mlx_pixel_put(&data->img3d, pos_x, pos_y, BLACK);
		step++;
	}
}

void	dist_rays_wall(t_data *data, double hit_x, double hit_y, int ray_id)
{
	double	dx;
	double	dy;
	double	dist;
	double	dist_reel;
	double	diff;

	dx = (hit_x - data->map->player_x);
	dy = (hit_y - data->map->player_y);
	dist = sqrt(dx * dx + dy * dy);
	diff = data->map->player_dir - data->ray.ray_angle;
	if (diff < -PI)
		diff += 2 * PI;
	else if (diff > PI)
		diff -= 2 * PI;
	dist_reel = dist * cos(diff);
	draw_wall(data, dist_reel, ray_id);
}

void	draw_wall(t_data *data, double dist_reel, int ray_id)
{
	double	wall_h;
	double	y_start;
	double	y_end;
	int		col;
	int		y;

	if (dist_reel < 0.1)
		dist_reel = 0.1;
	wall_h = (TILE / dist_reel) * D_P_PROJECT;
	y_start = (HEIGHT / 2) - (wall_h / 2);
	y_end = (HEIGHT / 2) + (wall_h / 2);
	if (y_start < 0)
		y_start = 0;
	if (y_end > HEIGHT)
		y_end = HEIGHT;
	col = ((double)ray_id / (double)NUM_RAYS * (double)WIDTH);
	// col = ray_id * (WIDTH /NUM_RAYS);
	y = y_start;
	while (y < y_end)
	{
		// my_mlx_pixel_put(&data->img3d, col, y, BLUE);
		draw_strips(data, col, y, BLUE);
		y++;
	}
}

void	draw_strips(t_data *data, int col, int y, int color)
{
	int	x;
	int	strips;

	strips = (WIDTH / NUM_RAYS);
	x = 0;
	while (x < strips)
	{
		my_mlx_pixel_put(&data->img3d, col + x, y, color);
		x++;
	}
}
// hypotenuse = Va2 + b2;

// Normaliser les mur si ca ondule
// double diff = player_dir - ray_angle;
// if (diff < 0)
//     diff += 2 * PI;
// if (diff > 2 * PI)
//     diff -= 2 * PI;
// dist_reel = dist * cos(diff);