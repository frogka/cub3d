/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:46 by jdutille          #+#    #+#             */
/*   Updated: 2025/09/29 20:27:00 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int main ()
{
   t_data data;

   data.mlx_ptr = mlx_init();
   data.win_ptr = mlx_new_window(data.mlx_ptr, LARGEUR, HAUTEUR
, "test");
data.img.img_ptr = mlx_new_image(data.mlx_ptr, LARGEUR, HAUTEUR);
data.img.addr = mlx_get_data_addr(data.img.img_ptr , &data.img.bpp, &data.img.line_len, &data.img.endian);
mlx_loop(data.mlx_ptr);
}

