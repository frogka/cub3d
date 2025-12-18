/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:01:18 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/18 19:05:05 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// gestion des textures avant fin du projet

int sotck_config( int fd, t_config *cfg)
{
	char *line;
	int i;

	i = 0;
	line = get_next_line(fd);
	while(line && ft_isspace(ft_isalpha(line[i])))
	{
		if (is_config_line(&line[i]))
		{
			if (parse_config(cfg, &line[i]))
			{
				printf("%s\n", cfg->no_text);
				// printf("%s\n", cfg->so_text);
			}
		}
		else
			free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break;
	}
	// i++;
	return 0;
}









/*
//charge les text
int	load_one_textures(t_data *data, int dir, char *path)
{
	data->tex[dir].img = mlx_xpm_file_to_image(data->mlx_ptr, path,
			data->tex[dir].width, data->tex[dir].height);
	if (!data->tex[dir].img)
	{
		return (0);
		// message d'erreur??
	}
	data->tex[dir].addr = mlx_get_data_addr(data->tex[dir].img,
			&data->tex[dir].bpp, &data->tex[dir].line_len,
			&data->tex[dir].endian);
	return (1);
}

//controle que les text aient ete chargees 
int	init_textures(t_data *data, t_config *cfg)
{
	if (!load_one_textures(data, NORTH, cfg->no_text))
		return (0);
	if (!load_one_textures(data, SOUTH, cfg->so_text))
		return (0);
	if (!load_one_textures(data, WEST, cfg->we_text))
		return (0);
	if (!load_one_textures(data, EAST, cfg->ea_text))
		return (0);
	return (1);
}*/
