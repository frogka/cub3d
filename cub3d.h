/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:37:57 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/03 23:49:12 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

// taille de l'ecran
# define LARGEUR 1200
# define HAUTEUR 800

# define TILE 64
# define PI 3.14

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
	double	player_x;
	double	player_y;
	double	player_dir;
	int		player_found;
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

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			check_valid_numbers(int r, int g, int b);
int			check_colors(char *line);
int			xrgb(int r, int g, int b);
void		parse_config(t_config *config, char *line);
int			is_config_line(char *line);
int			is_map_line(char *line);
char		**fill_map(int fd, t_map *map);
int			count_map_lines(int fd, t_map *map);

///////////MAP.C/////////////
void		draw_square(t_data *data, char c, int x, int y);
void		draw_map(t_map *map, t_data *data, int x, int y);

///////////PLAYER//////////////////
void check_numb_player(t_map *map, char *line, int x, int y);
void player_position(t_map *map, char c, int x, int y);


// faire le parsing de la map
// lecture 0 1 via gnl
// mettre couleur sol et mur en scindant l'ecran en 2 dans la hauteur
// ca permet d'avoir un faut 3d
// faire le raycasting

#endif