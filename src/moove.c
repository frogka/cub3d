/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/06 21:18:52 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keycode, t_map *map)
{
	if (keycode == KEY_LEFT)
		moove_left(map);
	if (keycode == KEY_RIGHT)
		moove_right(map);
	if (keycode == KEY_UP)
		moove_up(map);
	if (keycode == KEY_DOWN)
		moove_down(map);
	if (keycode == KEY_ESC)
		destroy(map);
	iter_reset(keycode, map);
	change_iter(keycode, map);
	return (0);
}

void moove_up(t_map *map, )
