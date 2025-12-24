/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:19:06 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/24 00:25:40 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_structure_data(t_data *data, t_map *map)
{
	data = malloc(sizeof(t_data));
	data->wall_hit = malloc(sizeof(double) * WIDTH);
	data->wall_side = malloc(sizeof(int) * WIDTH);
	if (!data || !data->wall_hit || !data->wall_side)
		return (1);
	data->map = map;
	data->ray.mapx = 0;
	data->ray.mapy = 0;
	data->right = 0;
	data->left = 0;
	data->up = 0;
	data->down = 0;
	data->pov_r = 0;
	data->pov_l = 0;
	data->esc = 0;
    return (0);
}

int	init_structure_map(t_map *map)
{
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	map->height = 0;
	map->width = 0;
	map->player_found = 0;
	map->posX = 0;
	map->posY = 0;
	return (0);
}

int init_structure_config(t_config *config)
{
    int i;
    
    i = 0;
    config = malloc(sizeof(t_config));
	if (!config)
		return (1);
	//remplacer par bzero
	while ( i < 6)
	{
		config->tex[i] = 0;
		i++;
	}
    return (0);
}