/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:19:06 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/26 16:34:38 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_structure_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->wall_hit = malloc(sizeof(double) * WIDTH);
	data->wall_side = malloc(sizeof(int) * WIDTH);
	if (!data->wall_hit || !data->wall_side)
	{
		free(data->wall_hit);
		free(data->wall_side);
		free(data);
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	return (data);
}

t_map	*init_structure_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

t_config	*init_structure_config(void)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	ft_memset(config, 0, sizeof(t_config));
	return (config);
}

void	free_all_structures(t_data *data, t_map *map, t_config *config)
{
	free(data->wall_hit);
	free(data->wall_side);
	free(data);
	free(map);
	free_config(config);
}