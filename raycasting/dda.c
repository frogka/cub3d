/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:20:12 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/11 21:41:01 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


//calcule de la distance joueur a la premiere frontiere
//
static void	init_dda_dist(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray;
	if (ray->ray_dx > 0)
	{
		ray->stepx = 1;
		ray->side_dx = (ray->mapx + 1 - data->map->player_x) * ray->delta_dx;
	}
	else
	{
		ray->stepx = -1;
		ray->side_dx = (data->map->player_x - ray->mapx) * ray->delta_dx;
	}
	if (ray->ray_dy > 0)
	{
		ray->stepy = 1;
		ray->side_dy = (ray->mapy + 1 - data->map->player_y ) * ray->delta_dy;
	}
	else
	{
		ray->stepy = -1;
		ray->side_dy = (data->map->player_y - ray->mapy) * ray->delta_dy;
	}
}


//initialise les variables pour le dda
//rayDirX=dirX+planeX∗cameraX;
void	init_dda(t_map *map, t_ray *ray, t_data *data)
{
	// Dans init_dda, juste avant les lignes que vous avez montrées
// printf("DEBUG: player_x: %f, player_y: %f\n", data->map->player_x, data->map->player_y);
	ray->ray_dx = map->dirX + map->planeX * map->cameraX; //cos(ray->ray_angle);
	ray->ray_dy = map->dirY + map->planeY * map->cameraX; //sin(ray->ray_angle); 
	// printf("DEBUG: map_x: %d, map_y: %d\n", ray->mapx, ray->mapy);
	ray->mapx = (int)(data->map->player_x);
	ray->mapy = (int)(data->map->player_y);
	ray->delta_dx = fabs(1 / ray->ray_dx);
	ray->delta_dy = fabs(1 / ray->ray_dy);
	init_dda_dist(data);
	ray->hit = 0;
}


//saut de frontiere en frontiere jusqu'au mur 
//permet d'atteindre le mur 
void	dda_steps(t_data *data, t_ray *ray)
{
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
		// printf("DEBUG: data: %p\n", data);
		if (!data) return; // ou gérez l'erreur
		// printf("DEBUG: data->map: %p\n", data->map);
		if (!data->map) return;
		// printf("DEBUG: data->map->grid: %p\n", data->map->grid);
		if (!data->map->grid) return;
		// printf("DEBUG: mapy: %d, mapx: %d\n", ray->mapy, ray->mapx);
		if (data->map->grid[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

//calcul la distance entre le joueur et le mur
//donc la longueur du rayon => perp_dist
double	dda_dist(t_data *data, t_ray *ray, int ray_id)
{
	double	perp_dist;
	double	wall_x;

		// printf("SALUT\n");
	if (ray->side == 0)
		perp_dist = (ray->mapx - data->map->player_x + (1 - ray->stepx)
				/ 2) / ray->ray_dx;
	else
		perp_dist = (ray->mapy - data->map->player_y + (1 - ray->stepy)
				/ 2) / ray->ray_dy;
	if (ray->side == 0)
		wall_x = data->map->player_y + perp_dist * ray->ray_dy;
	else
		wall_x = data->map->player_x + perp_dist * ray->ray_dx;
	wall_x -= floor(wall_x);
	data->wall_hit[ray_id] = wall_x;
	data->wall_side[ray_id] = ray->side;
	return (perp_dist);
}



void	draw_wall(t_data *data, t_ray *ray, int ray_id)
{
	double wall_h;
	int d_start;
	int d_end;
	double perp_dist;
	int color;

	perp_dist = dda_dist(data, ray, ray_id);
	wall_h = (1.0 / perp_dist) * data->proj_pl_dist;

	d_start = (int)(HEIGHT / 2) - (wall_h / 2);
	d_end = (int)(HEIGHT / 2) + (wall_h / 2);

	if (d_start < 0)
		d_start = 0;
	if (d_end >= HEIGHT)
		d_end = HEIGHT - 1;
	if (ray->side == 0)
		color = GREEN; //VERTICAL
	else	
		color = 0x0000FF; //HORIZONTALE
	int y = d_start;
	while (y <= d_end )
	{
		my_mlx_pixel_put(&data->img3d, ray_id, y, color);
		y++;
	}
}


//va permettre de gerer les textures
// void	wall_collision(t_data *data, t_ray *ray, int ray_id)
// {
// 	if (ray->side == 0)
// 	{
// 		if (ray->stepx == 1)
// 			ray->ray_dir[ray_id] = EAST;
// 		else
// 			ray->ray_dir[ray_id] = WEST;
// 	}
// 	else 
// 		if (ray->stepy == 1)
// 			ray->ray_dir[ray_id] = SOUTH;
// 		else
// 			ray->ray_dir[ray_id] = NORTH;
// }