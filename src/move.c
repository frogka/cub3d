/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/18 17:06:10 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// gestion des deplacements sur l'axe vertical
// Avancer D = (dirX, dirY)
// Reculer D = (-dirX, -dirY)
void	move_forw_back(t_data *data)
{
	double	next_x;
	double	next_y;

	printf("POSX = %f\n, ", data->map->posX);
	printf("POSY = %f\n, ", data->map->posY);
	next_x = data->map->posX + data->map->dirX * data->delta_v;
	next_y = data->map->posY + data->map->dirY * data->delta_v;
	if (check_collision(data, next_x, data->map->posY) == 0)
		data->map->posX = next_x;
	if (check_collision(data, data->map->posX, next_y) == 0)
		data->map->posY = next_y;
}

// gestion des deplacements sur l'axe horizontal
// Droite D = (-dirY, dirX)
// Gauche D = (dirY, -dirX)
void	move_rig_left(t_data *data)
{
	double	next_x;
	double	next_y;

	printf("POSX = %f\n, ", data->map->posX);
	printf("POSY = %f\n, ", data->map->posY);
	next_x = data->map->posX - data->map->dirY * data->delta_h;
	next_y = data->map->posY + data->map->dirX * data->delta_h;
	if (check_collision(data, next_x, data->map->posY) == 0)
		data->map->posX = next_x;
	if (check_collision(data, data->map->posX, next_y) == 0)
		data->map->posY = next_y;
}

// rotation du joueur sur la gauche
// oldDirX=dirX
// dirX = dirX⋅cos(rotSpeed) − dirY⋅sin(rotSpeed)
// dirY = -oldDirX⋅sin(rotSpeed) + dirY⋅cos(rotSpeed)
void	pov_left(t_data *data)
{
	double	old_dx;
	double	old_px;

	old_dx = data->map->dirX;
	old_px = data->map->planeX;
	data->map->dirX = data->map->dirX * cos(ROT_SPEED) + data->map->dirY
		* sin(ROT_SPEED);
	data->map->dirY = -old_dx * sin(ROT_SPEED) + data->map->dirY
		* cos(ROT_SPEED);
	data->map->planeX = data->map->planeX * cos(ROT_SPEED) + data->map->planeY
		* sin(ROT_SPEED);
	data->map->planeY = -old_px * sin(ROT_SPEED) + data->map->planeY
		* cos(ROT_SPEED);
}

// rotation du joueur sur la droite
// oldDirX=dirX
// dirX = dirX⋅cos(rotSpeed) − dirY⋅sin(rotSpeed)
// dirY = oldDirX⋅sin(rotSpeed) + dirY⋅cos(rotSpeed)
void	pov_right(t_data *data)
{
	double	old_dx;
	double	old_px;

	old_dx = data->map->dirX;
	old_px = data->map->planeX;
	data->map->dirX = data->map->dirX * cos(ROT_SPEED) - data->map->dirY
		* sin(ROT_SPEED);
	data->map->dirY = old_dx * sin(ROT_SPEED) + data->map->dirY
		* cos(ROT_SPEED);
	data->map->planeX = data->map->planeX * cos(ROT_SPEED) - data->map->planeY
		* sin(ROT_SPEED);
	data->map->planeY = old_px * sin(ROT_SPEED) + data->map->planeY
		* cos(ROT_SPEED);
}

// gestion des collisions
//?????????????
int	check_collision(t_data *data, double n_x, double n_y)
{
	int				x;
	int				y;
	int				i;
	static double	dx[4] = {R, R, -R, -R};
	static double	dy[4] = {R, -R, R, -R};

	i = 0;
	while (i < 4)
	{
		x = (n_x + dx[i]);
		y = (n_y + dy[i]);
		if (x < 0 || x >= data->map->width || y < 0 || y >= data->map->height)
			return (1);
		if (data->map->grid[y][x] == '1')
			return (1);
		i++;
	}
	return (0);
}
