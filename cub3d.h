/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:37:57 by jdutille          #+#    #+#             */
/*   Updated: 2025/09/30 19:20:05 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define LARGEUR 1200
# define HAUTEUR 800

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;

	t_image	img;
}			t_data;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	// ajouter position du joueur
}			t_map;

typedef struct s_config
{
	char	*no_text;
	char	*so_text;
	char	*ea_text;
	char	*we_text;
	int		floor;
	int		ceiling;
}			t_config;

#endif