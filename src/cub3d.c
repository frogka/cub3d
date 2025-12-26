/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:46 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/26 16:32:42 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// count widht et height max de la map
int	count_map_lines(int file, t_map *map)
{
	char	*line;
	int		len;
	int		count;

	len = 0;
	count = 0;
	line = NULL;
	while ((line = get_next_line(file)) != NULL)
	{
		printf("DEBUG LINE MAP : %s\n", line);
		if (is_map_line(line))
		{
		printf("DEBUG LINE MAP 2 : %s\n", line);
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
char	**fill_map(int file, t_map *map)
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
	while ((line = get_next_line(file)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_map_line(line))
		{
			// tout le if peut tenir dans une fontion pour < 25 lignes
			len = ft_strlen(line);
			printf("DEBUG : TAILLE de width: %d\n", map->width);
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
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
		{
			return (0);
			// fonction pour free grid et line et quitter le programme;
		}
		i++;
	}
	// printf("Caractere non valable\n");
	return (1);
}

// fonction qui check la validite des config
int	is_config_line(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(&line[i])) // mettre les \n et \0 ??
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && ft_isspace(&line[i + 2]))
		return (1);
	else if (ft_strncmp(&line[i], "C", 1) == 0  && ft_isspace(&line[i + 1]))
		return (1);
	else if (ft_strncmp(&line[i], "F", 1) == 0 && ft_isspace(&line[i + 1]))
		return (1);
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
	int		red;
	int		green;
	int		blue;
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
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	free_split(colors);
	if (check_valid_numbers(red, green, blue) == 1)
		return (xrgb(red, green, blue));
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
	int		file;
	t_data	*data;
	t_map	*map;
	t_config *config;

	data = 0;
	map = 0;
	config = 0;
	data = init_structure_data();
	if (!data)	
		return 1;
	map = init_structure_map();
	if (!map)
		return(free(data), 1);
	data->map = map;
	config = init_structure_config();
	if (!config)
		return (free_all_structures(data, map, config), 1);
	// t_ray *ray;
	
	// ray = malloc(sizeof(t_ray));
	// printf("DEBUG: Ptr ray: %p\n", ray);
	// map->grid = NULL;
	
	// faire une condition qui ouvre seulement si .cub
	file = open("map.cub", O_RDONLY);
	
	
	if (count_map_lines(file, map) == -1)
		return (1);
	
	// printf("width = %d, height = %d\n", map->width, map->height);
	close(file);
	file = open("map.cub", O_RDONLY);
	if (store_config(file, config))
		return (free_all_structures(data, map, config) ,1);
	close(file);
	file = open("map.cub", O_RDONLY);
	map->grid = fill_map(file, map);
	if (check_num_player(map))
		return (1);
	if (!map->grid)
	{
		perror("fill_map failed");
		return (1);
	}
	if (data->map == NULL)
    	printf("ERREUR : La map n'a pas été allouée !\n");
	close(file);
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

	init_minimap(map, data->m);
	
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

	init_hook(data);
	
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop_hook(data->mlx_ptr, handle_input, data);
	mlx_loop(data->mlx_ptr);
	// focniton pour traiter les 2 buffers
	return (0);
}
