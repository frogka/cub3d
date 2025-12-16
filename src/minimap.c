/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:55:13 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/16 01:25:29 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialissation des elemetns pour la map 2d
//??????????????
void	init_minimap(t_map *map, t_minimap *mini)
{
	double scalex;
	double scaley;

	mini->height = H_MINI;
	mini->width = W_MINI;
	scalex = (double)mini->width / (map->width * TILE);
	scaley = (double)mini->height / (map->height * TILE);
	if (scalex > scaley)
		mini->scale = scaley;
	else
		mini->scale = scalex;
	printf("scale minimap = %f\n", mini->scale);
}