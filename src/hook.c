/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:54:05 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/08 02:33:07 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keycode,t_data *data)
{
	//if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	//	moove_h(keycode, map, data);
    printf("handle_input reçoit data = %p\n", data);
    printf("adresse data = %p\n", data);
printf("adresse map  = %p\n", data->map);
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		moove_v(keycode, data);
	if (keycode == KEY_ESC)
		destroy(data);
    printf("%d\n", keycode);
	return (0);
}

void	init_hook(t_data *data)
{
    printf("init_hook reçoit un t_data* ? data = %p, &data = %p\n", data, &data);
    printf("adresse data = %p\n", data);
    printf("adresse map  = %p\n", data->map);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 02, 1L << 0, handle_input, data);
	//mlx_mouse_hook(data->win_ptr, mouse_hook, data);
}


int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}