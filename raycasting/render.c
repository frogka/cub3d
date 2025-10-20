/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:32:29 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/19 18:11:07 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_img(t_image *img, int height)
{
	ft_bzero(img->addr, height * img->line_len);
}

int	render(t_data *data)
{
	clear_img(&data->img3d, HEIGHT);
	clear_img(&data->img, HEIGHT_M);
	draw_rays(data);
	draw_map(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3d.img_ptr,
		0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
	return (0);
}

// void render_3d(t_data *data)
// {
//     draw_rays(data);
// }