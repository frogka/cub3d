/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:37:57 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/16 02:40:23 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdbool.h>
#include <sys/time.h>

// taille de l'ecran
# define WIDTH 1200
# define HEIGHT 800
# define W_MINI 300
# define H_MINI 250
# define MINI_S 0.25
# define SCALE

# define TILE 64
# define R 0.45
// # define RAYON TILE / 6 // cahnger ca
# define PI 3.1415926
# define SPEED 0.03
# define ROT_SPEED 0.02
# define D_P_PROJECT \
	((WIDTH / 2) / tan(FOV / 2)) // 32795.157510769
									// dist plqyer projection

// definir les couleurs
# define RED 0xFF0000
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define BLACK 0x000000

// definir les cotes
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

// key des touches clavier
enum					key
{
	KEY_ESC = 65307,
	KEY_RIGHT = 100,
	KEY_DOWN = 115,
	KEY_LEFT = 97,
	KEY_U = 65362,
	KEY_UP = 119,
	KEY_D = 65364,
	KEY_L = 65361,
	KEY_R = 65363,
};

// raycasting
# define FOV (66 * (PI / 180)) // 1.151917306 // 66 degres, 66 * pi/180
# define NUM_RAYS 1200

// gere les points pour les collisions
// typedef struct s_moves
// {
// 	double				dx[4];
// 	double					dy[4];
// }						t_moves;

typedef struct s_tex
{
	void				*img;
	int					*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_tex;

// structure qui gere l'affichage
typedef struct s_image
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_image;

typedef struct s_ray
{
	int					stepx;
	int					stepy;
	double				ray_dx;
	double				ray_dy;
	double				side_dx;
	double				side_dy;
	double				delta_dx;
	double				delta_dy;
	// int					*ray_dir;
	int					mapx;
	int					mapy;
	int					hit;
	int					side;
	double dist_cor; //
						// double				ray_angle;
}						t_ray;

// gere la connexion au server + l'image
typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	double				proj_pl_dist;
	double				*wall_hit;
	int					*wall_side;
	bool				up;
	bool				down;
	bool				left;
	bool				right;
	bool				pov_l;
	bool				pov_r;
	bool				esc;
	double				delta_h;
	double				delta_v;
	t_image				img;
	t_image				img3d;
	// t_moves				moves;
	t_ray				ray;
	t_tex				tex[4];
	struct s_map		*map;
	struct s_config		*config;
	struct s_minimap	*m;
}						t_data;

typedef struct s_minimap
{
	int					height;
	int					width;
	double				scale;
}						t_minimap;

// gere les infos de la map
typedef struct s_map
{
	char				**grid;
	int					height;
	int					width;
	double				posX;
	double				posY;
	double				dirX;
	double				dirY;
	double				planeX;
	double				planeY;
	double				cameraX;
	int					player_found;
	// ajouter position du joueur
}						t_map;

// gere les images et couleurs de la map
typedef struct s_config
{
	char				*no_text;
	char				*so_text;
	char				*ea_text;
	char				*we_text;
	int					floor;
	int					ceiling;
}						t_config;

///////////////CUB3D////////////////
void					my_mlx_pixel_put(t_image *img, int x, int y, int color);
int						check_valid_numbers(int r, int g, int b);
int						check_colors(char *line);
int						xrgb(int r, int g, int b);
void					parse_config(t_config *config, char *line);
int						is_config_line(char *line);
int						is_map_line(char *line);
char					**fill_map(int fd, t_map *map);
int						count_map_lines(int fd, t_map *map);
// char				**map_space(t_map *map, char **grid);

///////////MAP/////////////
int						check_map_closed(t_map *map);
int						flood_fill(char **cpy_grid, t_map *map, int x, int y);
char					**copy_map(char **grid, t_map *map);
void					draw_square(t_data *data, char c, int x, int y);
void					draw_map(t_map *map, t_data *data);
void					draw_player(t_map *map, t_data *data);

///////////PLAYER//////////////////
// void		check_numb_player(t_map *map, char *line, int x, int y);
void					set_player(t_map *map, int x, int y);
int						check_num_player(t_map *map);
void					player_position(t_map *map);
void					is_one_player(t_map *map, char *line);
void					set_direction(t_map *map, int x, int y);

void					set_virtual_plan(t_map *map, int x, int y);

long long	timestamp(void); ////////////////////////////////////////////////////

/////////////////MOOVE////////////////
void					move_forw_back(t_data *data);
void					move_rig_left(t_data *data);
void					pov_left(t_data *data);
void					pov_right(t_data *data);
int						check_collision(t_data *data, double n_x, double n_y);

//////////////////HOOK/////////////////
int						handle_input(t_data *data);
void					init_hook(t_data *data);
int						close_win(t_data *data);
void					destroy(t_data *data);
int						key_release(int key, t_data *data);
int						key_press(int key, t_data *data);
void					normalize_move(t_data *data);

/////////////////RAYCASTING/////////////////
// void					draw_rays(t_data *data);
// void					draw_one_ray(t_data *data, double ray_dx, double ray_dy,
// int ray_id);
// void					dist_rays_wall(t_data *data, double hit_x, double hit_y,
// int ray_id);
// void					draw_wall(t_data *data, double dist_reel, int ray_id);
// void					draw_strips(t_data *data, int col, int y, int color);

////////////////////DDA/////////////////////
void					draw_wall(t_data *data, t_ray *ray, int ray_id);
double					dda_dist(t_data *data, t_ray *ray, int ray_id);
void					init_dda(t_map *map, t_ray *ray, t_data *data);
void					dda_steps(t_data *data, t_ray *ray);

void					raycast_main(t_data *data);

/////////////////RENDER/////////////////////
int						render(t_data *data);

/////////////////MINIMAP///////////////////
void					init_minimap(t_map *map, t_minimap *mini);

////////////////TEXTURES///////////////////////
int sotck_config( int fd);


// faire le parsing de la map
// lecture 0 1 via gnl
// mettre couleur sol et mur en scindant l'ecran en 2 dans la hauteur
// ca permet d'avoir un faut 3d
// faire le raycasting

#endif