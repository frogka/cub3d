/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:37:57 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/18 16:23:05 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

// taille de l'ecran
# define WIDTH 1200
# define HEIGHT 800
# define WIDTH_M 300
# define HEIGHT_M 200

# define TILE 64
# define TILE_P 7       // 7 15 ou 11, uneven numbers
# define RAYON TILE / 6 // cahnger ca
# define PI 3.1415926
# define SPEED 2
# define D_P_PROJECT \
	((WIDTH / 2) / tan(FOV / 2)) // 32795.157510769
									// dist plqyer projection

// definir les couleurs
# define RED 0xFF0000
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define BLACK 0x000000

// keycode des touches clavier
# define KEY_ESC 65307
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_G 65361
# define KEY_H 65362
# define KEY_D 65363
# define KEY_B 65364

// raycasting
# define FOV 1.047197551 // 60 degres, PI/3
# define NUM_RAYS 640

// gere les points pour les collisions
typedef struct s_moves
{
	int				dx[4];
	int				dy[4];
}					t_moves;

// structure qui gere l'affichage
typedef struct s_image
{
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_image;

typedef struct s_ray
{
	// double			ray_x;
	// double			ray_y;
	// double			hit_x;
	// double			hit_y;
	// double			ray_dir_x;
	// double			ray_dir_y;
	double			ray_angle;
	// double			dist_reel;
	// int				ray_id;

}					t_ray;

// gere la connexion au server + l'image
typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			img;
	t_image			img3d;
	t_moves			moves;
	t_ray			ray;
	struct s_map	*map;
	struct s_config	*config;
}					t_data;

// gere les infos de la map
typedef struct s_map
{
	char			**grid;
	int				height;
	int				width;
	double			player_x;
	double			player_y;
	double			player_dir;
	int				player_found;
	// ajouter position du joueur
}					t_map;

// gere les images et couleurs de la map
typedef struct s_config
{
	char			*no_text;
	char			*so_text;
	char			*ea_text;
	char			*we_text;
	int				floor;
	int				ceiling;
}					t_config;

///////////////CUB3D////////////////
void				my_mlx_pixel_put(t_image *img, int x, int y, int color);
int					check_valid_numbers(int r, int g, int b);
int					check_colors(char *line);
int					xrgb(int r, int g, int b);
void				parse_config(t_config *config, char *line);
int					is_config_line(char *line);
int					is_map_line(char *line);
char				**fill_map(int fd, t_map *map);
int					count_map_lines(int fd, t_map *map);
// char				**map_space(t_map *map, char **grid);

///////////MAP/////////////
int					check_map_closed(t_map *map);
int					flood_fill(char **cpy_grid, t_map *map, int x, int y);
char				**copy_map(char **grid, t_map *map);
void				draw_square(t_data *data, char c, int x, int y);
void				draw_map(t_map *map, t_data *data);
void				draw_player(t_map *map, t_data *data);

///////////PLAYER//////////////////
// void		check_numb_player(t_map *map, char *line, int x, int y);
void				set_player(t_map *map, int x, int y);
int					check_num_player(t_map *map);
void				player_position(t_map *map);
void				is_one_player(t_map *map, char *line);

/////////////////MOOVE////////////////
void				move_v(int keycode, t_data *data);
void				move_h(int keycode, t_data *data);
void				pov_left(t_data *data);
void				pov_right(t_data *data);
int					check_collision(t_data *data, double n_x, double n_y);

//////////////////HOOK/////////////////
int					handle_input(int keycode, t_data *data);
void				init_hook(t_data *data);
int					close_win(t_data *data);
void				destroy(t_data *data);

/////////////////RAYCASTING/////////////////
void				draw_rays(t_data *data);
void	draw_one_ray(t_data *data, double ray_dx, double ray_dy); //,
																// int ray_id);
void	dist_rays_wall(t_data *data, double hit_x, double hit_y); //,
																// int ray_id);
void				draw_wall(t_data *data, double dist_reel, int ray_id);

// faire le parsing de la map
// lecture 0 1 via gnl
// mettre couleur sol et mur en scindant l'ecran en 2 dans la hauteur
// ca permet d'avoir un faut 3d
// faire le raycasting

#endif