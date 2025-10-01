/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:37:57 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/01 20:22:29 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

//taille de l'ecran
# define LARGEUR 1200
# define HAUTEUR 800

# define TILE 10

// definir les couleurs
# define RED 0xFF0000
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define BLACK 0x000000

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//faire le parsing de la map
//lecture 0 1 via gnl
//mettre couleur sol et mur en scindant l'ecran en 2 dans la hauteur
//ca permet d'avoir un faut 3d 
//faire le raycasting

#endif