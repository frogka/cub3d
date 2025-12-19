/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:46 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/19 18:37:18 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// count widht et height max de la map
int	count_map_lines(int fd, t_map *map)
{
	char	*line;
	int		len;
	int		count;

	len = 0;
	count = 0;
	line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_map_line(line) == 0)
		{
			count++;
			len = ft_strlen(line);
			// printf("%d\n", len);
			if (len > map->width)
				map->width = len;
			free(line);
		}
		else
		{
			free(line);
			// return (-1);
		}
	}
	map->height = count;
	return (count);
}

// forme une map de width et height identique
char	**fill_map(int fd, t_map *map)
{
	int		i;
	int		len;
	char	*line;
	char	**grid;

	// int		j;
	printf("1width = %d, height = %d\n", map->width, map->height);
	grid = malloc(sizeof(char *) * (map->height + 1));
	if (!grid)
		return (NULL);
	i = 0;
	// j = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_map_line(line) == 0)
		{
			// tout le if peut tenir dans une fontion pour < 25 lignes
			len = ft_strlen(line);
			grid[i] = malloc(sizeof(char) * (map->width + 1));
			ft_memcpy(grid[i], line, len);
			while (len < map->width)
				grid[i][len++] = ' ';
			grid[i][len] = '\0';
			is_one_player(map, grid[i]);
			i++;
		}
		free(line);
	}
	grid[i] = NULL;
	// printf("2width = %d, height = %d\n", map->width, map->height);
	// j = 0;
	// while (grid[j])
	// {
	// 	printf("%s\n", grid[j]);
	// 	printf("%zu\n", ft_strlen(grid[j]));
	// 	j++;
	// }
	return (grid);
}

// pbl qunas joeur est a l'extremite + P quand la lettre est != du joueur
// controle la validite des car de la map
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
		{
			return (0);
			// fonction pour free grid et line et quitter le programme;
		}
		i++;
	}
	printf("Caractere non valable\n");
	return (1);
}

// fonction qui check la validite des config
int	is_config_line(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(&line[i])) // mettre les \n et \0 ??
		i++;
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (line[i] == 'C' && ft_isspace(&line[i + 1]))
		return (1);
	else if (line[i] == 'F' && ft_isspace(&line[i + 1]))
		return (1);
	// else
	//   return ; //message d'erreur
	//
	// AJOUT d'une conditon dans le main que si on a une map line
	// et que les configs sont != de 6 ca va pas
	// ont doit avoir toutes les configs puis la map
	return (0);
}

// fonction qui atttribut les config a la structure
// ajout d'un char temporaire ??
//
// Faire un check prealable que la fin du passe des configs de
// NO EA WE SO termine bien par xpm
// void	*parse_config(t_config *config, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_isspace(&line[i]))
// 		i++;
// 	if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(&line[i + 2]))
// 		config->no_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
// 	else if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(&line[i + 2]))
// 		config->ea_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
// 	else if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(&line[i + 2]))
// 		config->we_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
// 	else if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isspace(&line[i + 2]))
// 		config->so_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
// 	else if (line[i] == 'C' && ft_isspace(&line[i + 1]))
// 		config->ceiling = check_colors(ft_skip_spaces(&line[i + 1]));
// 	else if (line[i] == 'F' && ft_isspace(&line[i + 1]))
// 		config->floor = check_colors(ft_skip_spaces(&line[i + 1]));
// 	return (config);
// }

// faire une focntin qui check tout le .cub et qui appelle les fonctions annexes
// a chque etapes
// 1er check que les configs sont valides
// si valide alors attributs aux structures
// sinon message d'erreur

int	xrgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// check la validite des couleurs de Ceil et Floor
int	check_colors(char *line)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	colors = ft_split(line, ',');
	while (colors[i])
		i++;
	if (i != 3)
	{
		free_split(colors);
		return (-1);
		// message d'erreur
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free_split(colors);
	if (check_valid_numbers(r, g, b) == 1)
		return (xrgb(r, g, b));
	return (-1);
	// message d'erreur sur la validite des nombres
}

// check la validite des nombres
int	check_valid_numbers(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0); // message d'erreur
	return (1);
}

// coloris le pixel a l'endroit souhaite
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	int		fd;
	t_data	*data;
	t_map	*map;
	t_config *cfg;

	cfg = malloc(sizeof(t_config));
	// t_ray *ray;
	data = malloc(sizeof(t_data));
	// ray = malloc(sizeof(t_ray));
	// printf("DEBUG: Ptr ray: %p\n", ray);
	map = malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	map->player_found = 0;
	map->posX = 0;
	map->posY = 0;
	data->ray.mapx = 0;
	data->ray.mapy = 0;
	data->right = 0;
	data->left = 0;
	data->up = 0;
	data->down = 0;
	data->pov_l = 0;
	data->pov_l = 0;
	data->esc = 0;
	data->wall_hit = malloc(sizeof(double) * WIDTH);
	data->wall_side = malloc(sizeof(int) * WIDTH);
	if (!data->wall_hit || !data->wall_side)
	{
		printf("ZEUB\n");
		return (1);
	}
	// map->grid = NULL;
	data->map = map;
	// printf("DEBUG playerx : %f, playery : %f\n", data->map->posX,
	// data->map->posY);
	// printf("map addr main = %p\n", map);
	if (!map)
		exit(1);
	// faire une condition qui ouvre seulement si .cub
	fd = open("map.cub", O_RDONLY);
	// printf("after open: fd = %d\n", fd);
	// while ((line = get_next_line(fd)))
	// {
	//    printf("%s\n", line);
	//    if (is_map_line(line))
	//    {
	//       free(line);
	//       break ;
	//    }
	//    free(line);
	// }
	// while (init_textures(data, cfg) != 0)
	sotck_config(fd, cfg);
	if (count_map_lines(fd, map) == -1)
		return (1);
	// printf("width = %d, height = %d\n", map->width, map->height);
	close(fd);
	fd = open("map.cub", O_RDONLY);
	
	// fill_map(fd, map);
	map->grid = fill_map(fd, map);
	if (check_num_player(map))
		return (1);
	if (!map->grid)
	{
		perror("fill_map failed");
		return (1);
	}
	player_position(map);
	if (check_map_closed(map))
	{
		free_split(map->grid);
		free(map);
		return (1);
	}
	data->proj_pl_dist = (WIDTH / 2) / tan(FOV / 2);
	printf("DEBUG : %f\n", tan(FOV / 2));
	printf("DEBUG 2 : %f\n", data->proj_pl_dist);
	data->m = malloc(sizeof(t_minimap));
	// m->height = 0;
	// m->width = 0;
	// m->scale = 0;
	// data.m = m;
	init_minimap(map, data->m);
	// free_split(copy_map(map->grid, map));
	// printf("%lf\n", map->posX);
	// printf("%lf\n", map->posY);
	// printf("%lf\n", map->player_dir);
	// printf("adresse data = %p\n", &data);
	// printf("adresse map  = %p\n", data.map);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	// rendu 3d
	data->img3d.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img3d.addr = mlx_get_data_addr(data->img3d.img_ptr, &data->img3d.bpp,
			&data->img3d.line_len, &data->img3d.endian);
	// pour minimap
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, W_MINI, H_MINI);
	// printf("FGASDFSDF\n");
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	// map->posX);
	// map->posY);
	// // printf("%lf\n",
	// map->player_dir);
	// // printf("adresse data =
	// %p\n",
	// &data);
	// // printf("adresse map  =
	// %p\n",
	// data.map);
	// draw_rays(&data);
	// draw_map(map,
	// &data);
	// mlx_put_image_to_window(data.mlx_ptr,
	// data.win_ptr,
	// data.img3d.img_ptr,
	// 0,
	// 0);
	// mlx_put_image_to_window(data.mlx_ptr,
	// data.win_ptr,
	// data.img.img_ptr,
	// 20,
	// 20);
	init_hook(data);
	// printf("DEBUG 33: posX: %f, posY: %f\n", data->map->posX,
	// data->map->posY);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop_hook(data->mlx_ptr, handle_input, data);
	mlx_loop(data->mlx_ptr);
	// focniton pour traiter les 2 buffers
	return (0);
}
