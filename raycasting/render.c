/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:32:29 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/11 00:55:17 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_img(t_image *img, int height)
{
	ft_bzero(img->addr, height * img->line_len);
}

// void clear_img(t_image *img, int height)
// {
//     int y, x;
//     char *pixel;

//     ft_bzero(img->addr, height * img->line_len);
//     // colorier tout en gris clair
//     y = 0;
//     while (y < height)
//     {
//         x = 0;
//         while (x < img->line_len / 4) // chaque pixel = 4 octets
//         {
//             pixel = img->addr + (y * img->line_len + x * 4);
//             *(int *)pixel = 0x00AAAAAA; // gris clair
//             x++;
//         }
//         y++;
//     }
// }

int	render(t_data *data)
{
	// clear_img(&data->img3d, HEIGHT);
	// clear_img(&data->img, H_MINI);
	raycast_main(data);
	draw_map(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3d.img_ptr,
		0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0); // valeur oporu decaler a la marge
	return (0);
}

// void render_3d(t_data *data)
// {
//     draw_rays(data);
// }