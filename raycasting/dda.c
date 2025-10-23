/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:20:12 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/23 21:26:14 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_ray *ray, t_data *data)
{
	ray->ray_dx = cos(ray->ray_angle);
	ray->ray_dy = sin(ray->ray_angle);
	ray->mapx = (int)(data->map->player_x / TILE);
	ray->mapy = (int)(data->map->player_y / TILE);
	ray->delta_dx = fabs(1 / ray->ray_dx);
	ray->delta_dy = fabs(1 / ray->ray_dy);

	init_dda_dist(data);
	ray->hit = 0;
}

static void	init_dda_dist(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray;
	if (ray->ray_dx > 0)
	{
		ray->stepx = 1;
		ray->side_dx = (ray->mapx + 1 - data->map->player_x / TILE)
			* ray->delta_dx;
	}
	else
	{
		ray->stepx = -1;
		ray->side_dx = (data->map->player_x / TILE - ray->mapx) * ray->delta_dx;
	}
	if (ray->ray_dy > 0)
	{
		ray->stepy = 1;
		ray->side_dy = (ray->mapy + 1 - data->map->player_y / TILE)
			* ray->delta_dy;
	}
	else
	{
		ray->stepy = -1;
		ray->side_dy = (data->map->player_y / TILE - ray->mapy) * ray->delta_dy;
	}
}

static void	dda_steps(t_ray *ray)
{
	t_data	*data;

	while (ray->hit == 0)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (data->map->grid[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

static void	dda_dist(t_data *data, t_ray *ray)
{
	double dist_ray;

	if (ray->side == 0)
		dist_ray = (ray->mapx - data->map->player_x / TILE + (1 - ray->stepx)
				/ 2) / ray->ray_dx;
	else
		dist_ray = (ray->mapy - data->map->player_y / TILE + (1 - ray->stepy
					/ 2)) / ray->ray_dy;
	ray->dist_cor = dist_ray * cos(ray->ray_angle - data->map->player_dir);
}

void draw_wall(t_data *data, t_ray * ray)
{
	double wall_h;
	double d_start;
	double d_end;

	data->proj_pl_dist = (WIDTH / 2) / tan(FOV/2); 
	wall_h = (TILE / data->ray.dist_cor) * data->proj_pl_dist;
	d_start = (HEIGHT / 2) - (wall_h / 2);
	d_end = (HEIGHT / 2) + (wall_h / 2);

	if (d_start < 0)
		d_start = 0;
	if (d_end > HEIGHT)
		d_end = HEIGHT - 1;
}