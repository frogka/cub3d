/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:54:05 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/23 22:21:01 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

// recup les event claviers pour les deplacements
// changer car deplacements simultanee en focntionnent pas
int	handle_input(t_data *data)
{
	// long long start = timestamp();
	// printf("TIME 1 : %lld\n", timestamp() - start );
	normalize_move(data);
	if (data->delta_v != 0.0)
		move_forw_back(data);
	if (data->delta_h != 0.0)
		move_rig_left(data);
	if (data->pov_r == true)
		pov_right(data);
	if (data->pov_l == true)
		pov_left(data);
	if (data->esc == true)
		destroy(data);
	raycast_main(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3d.img_ptr,
		0, 0);
	// printf("TIME 2 : %lld\n",timestamp() - start );
	return (0);
}

void	normalize_move(t_data *data)
{
	double	l;

	data->delta_h = 0.0;
	data->delta_v = 0.0;
	if (data->up == true)
		data->delta_v += 1;
	if (data->down == true)
		data->delta_v -= 1;
	if (data->right == true)
		data->delta_h += 1;
	if (data->left == true)
		data->delta_h -= 1;
	l = sqrt(data->delta_h * data->delta_h + data->delta_v * data->delta_v);
	if (l > 1.0)
	{
		data->delta_h = data->delta_h / l;
		data->delta_v = data->delta_v / l;
	}
	data->delta_h = data->delta_h * SPEED;
	data->delta_v = data->delta_v * SPEED;
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_UP || key == KEY_U)
	{
		if (data->up == true)
			return (0);
		data->up = true;
	}
	else if (key == KEY_RIGHT)
		data->right = true;
	else if (key == KEY_DOWN || key == KEY_D)
		data->down = true;
	else if (key == KEY_LEFT)
		data->left = true;
	else if (key == KEY_L)
		data->pov_l = true;
	else if (key == KEY_R)
		data->pov_r = true;
	else if (key == KEY_ESC)
		data->esc = true;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_UP || key == KEY_U)
		data->up = false;
	if (key == KEY_RIGHT)
		data->right = false;
	if (key == KEY_DOWN || key == KEY_D)
		data->down = false;
	if (key == KEY_LEFT)
		data->left = false;
	if (key == KEY_L)
		data->pov_l = false;
	if (key == KEY_R)
		data->pov_r = false;
	if (key == KEY_ESC)
		data->esc = false;
	return (0);
}

// initilalise les events claviers + la fermeture de la fenetre
void	init_hook(t_data *data)
{
	// printf("init_hook reçoit un t_data* ? data = %p, &data = %p\n", data,
	// 	&data);
	// printf("adresse data = %p\n", data);
	// printf("adresse map  = %p\n", data->map);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 02, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 03, 1L << 1, key_release, data);
	// mlx_key_hook(data->win_ptr, handle_input, data);
	// mlx_mouse_hook(data->win_ptr, mouse_hook, data);
}

// fermeture de la fenetre via la X
int	close_win(t_data *data)
{
	// free(data->config->ceiling);
	// free(data->config->floor);
	// free(data->config->ea_text);
	// free(data->config->so_text);
	// free(data->config->no_text);
	// free(data->config->we_text);
	free_split(data->map->grid);
	free(data->map);
	free(data->m);
	free_config(data->config);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

// fermeture de la fenetre via ESC
void	destroy(t_data *data)
{
	// free(data->config->ceiling);
	// free(data->config->floor);
	// free(data->config->ea_text);
	// free(data->config->so_text);
	// free(data->config->no_text);
	// free(data->config->we_text);
	free_split(data->map->grid);
	free(data->map);
	free(data->m);
	free_config(data->config);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	int i;
	i = 0;
	while (i < 6)
	{
		if (config->tex[i])
			free(config->tex[i]);
		i++;
	}
}