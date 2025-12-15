/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/15 04:35:37 by jdutille         ###   ########.fr       */
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
	double	marge;
	int		sign;

	marge = 0.8;
	sign = 1;
	// printf("adresse data = %p\n", data);
	// printf("adresse map  = %p\n", data->map);
	// printf("DEBUG : %f, %f\n", data->map->posX, data->map->posY);
	printf("POSX = %f\n, ", data->map->posX);
	printf("POSY = %f\n, ", data->map->posY);
	if (data->delta_v < 0)
		sign *= -1;
	next_x = data->map->posX + data->map->dirX * data->delta_v;
	next_y = data->map->posY + data->map->dirY * data->delta_v;
	if (data->map->grid[(int)(data->map->posY)][(int)(next_x + data->map->dirX
			* marge * sign)] != '1')
		data->map->posX = next_x;
	if (data->map->grid[(int)(next_y + data->map->dirY * marge
			* sign)][(int)(data->map->posX)] != '1')
		data->map->posY = next_y;
}

// gestion des deplacements sur l'axe horizontal
// Droite D = (-dirY, dirX)
// Gauche D = (dirY, -dirX)
void	move_rig_left(t_data *data)
{
	double	next_x;
	double	next_y;
	// double	check_x_pos;
	// double	check_y_pos;
	// double	check_x_neg;
	// double	check_y_neg;
	double	marge;
	int		sign;

	marge = 0.5;
	sign = 1;
	printf("POSX = %f\n, ", data->map->posX);
	printf("POSY = %f\n, ", data->map->posY);
	next_x = data->map->posX - data->map->dirY * data->delta_h;
	next_y = data->map->posY + data->map->dirX * data->delta_h;

	if (data->delta_h < 0)
		sign *= -1;
	// check_x_pos = data->map->posX + data->map->dirX * marge;
	// check_x_neg = data->map->posX - data->map->dirX * marge;
	// check_y_pos = data->map->posY + data->map->dirY * marge;
	// check_y_neg = data->map->posY - data->map->dirY * marge;
	// if (data->map->grid[(int)(check_y_pos)][(int)next_x] != '1'
	// 	&& data->map->grid[(int)(check_y_neg)][(int)next_x] != '1')
	// 	data->map->posX = next_x;
	// if (data->map->grid[(int)next_y][(int)check_x_pos] != '1'
	// 	&& data->map->grid[(int)(next_y)][(int)check_x_neg] != '1')
	// 	data->map->posY = next_y;
	if (data->map->grid[(int)(data->map->posY)][(int)(next_x
			+ (-data->map->dirY) * marge * sign)] != '1')
		data->map->posX = next_x;
	if (data->map->grid[(int)(next_y + data->map->dirX * marge
			* sign)][(int)(data->map->posX)] != '1')
		data->map->posY = next_y;
}

// rotation du joueur sur la gauche
// oldDirX=dirX
// dirX = dirX⋅cos(rotSpeed) − dirY⋅sin(rotSpeed)
// dirY = -oldDirX⋅sin(rotSpeed) + dirY⋅cos(rotSpeed)
void	pov_left(t_data *data)
{
	double	oldDx;
	double	oldPx;

	oldDx = data->map->dirX;
	oldPx = data->map->planeX;
	data->map->dirX = data->map->dirX * cos(ROT_SPEED) + data->map->dirY
		* sin(ROT_SPEED);
	data->map->dirY = -oldDx * sin(ROT_SPEED) + data->map->dirY
		* cos(ROT_SPEED);
	data->map->planeX = data->map->planeX * cos(ROT_SPEED) + data->map->planeY
		* sin(ROT_SPEED);
	data->map->planeY = -oldPx * sin(ROT_SPEED) + data->map->planeY
		* cos(ROT_SPEED);
}

// rotation du joueur sur la droite
// oldDirX=dirX
// dirX = dirX⋅cos(rotSpeed) − dirY⋅sin(rotSpeed)
// dirY = oldDirX⋅sin(rotSpeed) + dirY⋅cos(rotSpeed)
void	pov_right(t_data *data)
{
	double	oldDx;
	double	oldPx;

	oldDx = data->map->dirX;
	oldPx = data->map->planeX;
	data->map->dirX = data->map->dirX * cos(ROT_SPEED) - data->map->dirY
		* sin(ROT_SPEED);
	data->map->dirY = oldDx * sin(ROT_SPEED) + data->map->dirY * cos(ROT_SPEED);
	data->map->planeX = data->map->planeX * cos(ROT_SPEED) - data->map->planeY
		* sin(ROT_SPEED);
	data->map->planeY = oldPx * sin(ROT_SPEED) + data->map->planeY
		* cos(ROT_SPEED);
}

// gestion des collisions
//?????????????
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
		check_x = (n_x + data->moves.dx[i]) > 2.5;
		check_y = (n_y + data->moves.dy[i]) > 2.5;
		if (check_x < 0 || check_x > data->map->width || check_y < 0
				|| check_y > data->map->height) //=
			return (1);
		if (data->map->grid[check_y][check_x] == '1')
			return (1);
		i++;
	}
	return (0);
}
