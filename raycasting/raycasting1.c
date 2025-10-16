/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:52:44 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/17 00:21:07 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rays(t_data *data)
{
	double	rays_angle;
	int		i;

	rays_angle = data->map->player_dir - FOV / 2;
	i = 0;
	while (i < NUM_RAYS)
	{
		// appel fonction pour 1 rayon
		data->ray.ray_dir_x = cos(rays_angle);
		data->ray.ray_dir_y = sin(rays_angle);
        data->ray.ray_angle = rays_angle;
        if (i % 10 == 0)
		    draw_one_ray(data, i);
		rays_angle += FOV / NUM_RAYS;
		i++;
	}
}

void	draw_one_ray(t_data *data, int ray_id)
{
	double	pos_x;
	double	pos_y;
	int		x;
	int		y;
	int		i;

	pos_x = data->map->player_x;
	pos_y = data->map->player_y;
	i = 0;
	while (i < 300)
	{
		pos_x += data->ray.ray_dir_x * 1;
		pos_y += data->ray.ray_dir_y * 1;
		x = pos_x / TILE;
		y = pos_y / TILE;
		if (x < 0 || x >= data->map->width || y < 0 || y >= data->map->height)
			return ;
		if (data->map->grid[y][x] == '1')
		{
			data->ray.hit_x = pos_x;
			data->ray.hit_y = pos_y;
			data->ray.ray_id = ray_id;
			return ;
		}
		else
			my_mlx_pixel_put(data, pos_x, pos_y, BLACK);
		i++;
	}
}

void	dist_rays_wall(t_data *data)
{
	double	dx;
	double	dy;
	double	dist;
    // double dist_reel;

	dx = (data->ray.hit_x - data->map->player_x);
	dy = (data->ray.hit_y - data->map->player_y);
	dist = sqrt(dx * dx + dy * dy);
    data->ray.dist_reel = dist * cos(data->map->player_dir - data->ray.ray_angle);
    
    printf("angle = %.2f°, distance brute = %.2f, corrigée = %.2f\n",
       data->ray.ray_angle * (180 / PI), dist, data->ray.dist_reel);
}

void draw_wall(t_data *data)
{
	double wall_h;
	double y_start;
	double y_end;
	int col;
	int y;

	wall_h = (TILE / data->ray.dist_reel) * D_P_PROJECT;
	y_start = (HEIGHT / 2) - (wall_h / 2);
	y_end   = (HEIGHT / 2) + (wall_h / 2);

	if (y_start < 0)
		y_start = 0;
	if (y_end > HEIGHT)
		y_end = HEIGHT;
	col = data->ray.ray_id * (WIDTH / NUM_RAYS);
	y = y_start;
	while (y++ < y_end)
		my_mlx_pixel_put(data, col, y, RED);

}

// hypotenuse = Va2 + b2;
