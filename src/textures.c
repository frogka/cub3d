/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:01:18 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/20 21:06:03 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// gestion des textures avant fin du projet

int	store_config(int file, t_config *cfg)
{
	char	*line;
	char	**tab;

	line = get_next_line(file);
	while (is_map_line(line) == 1)
	{
		if (config_full(cfg))
		{
			free(line);
			break;
		}
		tab = ft_split(line, ' ');
		if (tab && tab[0])
		{
			if (strncmp(tab[0], "NO", 3) == 0 && tab[1] && cfg->no_text == NULL)
				cfg->no_text = ft_strtrim(tab[1], "\n");
			else if (strncmp(tab[0], "SO", 3) == 0 && tab[1]
				&& cfg->so_text == NULL)
				cfg->so_text = ft_strtrim(tab[1], "\n");
			else if (strncmp(tab[0], "EA", 3) == 0 && tab[1]
				&& cfg->ea_text == NULL)
				cfg->ea_text = ft_strtrim(tab[1], "\n");
			else if (strncmp(tab[0], "WE", 3) == 0 && tab[1]
				&& cfg->we_text == NULL)
				cfg->we_text = ft_strtrim(tab[1], "\n");
			else if (strncmp(tab[0], "F", 2) == 0 && tab[1]
				&& cfg->floor == NULL)
				cfg->floor = ft_strtrim(tab[1], "\n");
			else if (strncmp(tab[0], "C", 2) == 0 && tab[1]
				&& cfg->ceiling == NULL)
				cfg->ceiling = ft_strtrim(tab[1], "\n");
			else
				printf("DOUBLONS %s\n", line);
		}
		free_split(tab);
		free(line);
		line = get_next_line(file);
	}
	return (0);
}

int	config_full(t_config *cfg)
{
	return (cfg->ceiling  && cfg->floor && cfg->no_text
		&& cfg->so_text && cfg->ea_text && cfg->we_text);
}

/*

int	count_textures(t_config *cfg , int count)
{
	if (cfg->ea_text == NULL)
		return (1);
	else if (cfg->no_text == NULL)
		return(1);
	else if (cfg->so_text == NULL)
		return (1);
	else if (cfg->we_text == NULL)
		return (1);
	else if (cfg->floor == 0)
		return(1);
	else if (cfg->ceiling == 0)
		return (1);
	else
		count++;
	if (count == 6)
		return (count);
	return (0);
}





// //charge les text
// int	load_one_textures(t_data *data, int dir, char *path)
// {
// 	data->tex[dir].img = mlx_xpm_file_to_image(data->mlx_ptr, path,
// 			data->tex[dir].width, data->tex[dir].height);
// 	if (!data->tex[dir].img)
// 	{
// 		return (0);
// 		// message d'erreur??
// 	}
// 	data->tex[dir].addr = mlx_get_data_addr(data->tex[dir].img,
// 			&data->tex[dir].bpp, &data->tex[dir].line_len,
// 			&data->tex[dir].endian);
// 	return (1);
// }


// //controle que les text aient ete chargees
// int	init_textures(t_data *data, t_config *cfg)
// {
// 	if (!load_one_textures(data, NORTH, cfg->no_text))
// 		return (0);
// 	if (!load_one_textures(data, SOUTH, cfg->so_text))
// 		return (0);
// 	if (!load_one_textures(data, WEST, cfg->we_text))
// 		return (0);
// 	if (!load_one_textures(data, EAST, cfg->ea_text))
// 		return (0);
// 	if (cfg->ceiling == 0)
// 		return (0);
// 	if (cfg->floor == 0)
// 		return (0);
// 	return (1);
// }
*/