/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:20:12 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/23 04:10:20 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_ray *ray, t_data *data, double r_angle)
{
	ray->ray_dx = cos(r_angle);
	ray->ray_dy = sin(r_angle);
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
			//
			//appeler draw walls??
	}
}
