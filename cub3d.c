/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:46 by jdutille          #+#    #+#             */
/*   Updated: 2025/09/30 19:54:54 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_map_lines(int fd, t_map *map)
{
   char *line;
   int count = 0;
   
   while ((line = get_next_line(fd)) != NULL)
   {
      if (ft_strchr(line, '1') || ft_strchr(line, '0'))
         count++;
      free(line);
   }
   map->height = count;
   return (count);
}
char **fill_map(int fd, t_map *map)
{
   int i;
   char *line;
   char **grid;

   grid = malloc(sizeof(char *) * (map->height + 1));
   if (!grid)
      return(NULL);
   i = 0;
   while ((line = get_next_line(fd)) != NULL)
   {
      if (ft_strchr(line, '1') || ft_strchr(line, '0'))
      {
         grid[i] = ft_strdup(line);
         i++;
      }
      free(line);
   }
   grid[i] = NULL;
   return(grid);
}

int is_map_line(char *line)
{
   int i;

   i = 0;
   while ((line[i] == '\n' || line[i] == '\0'))
   {
      if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
         return 0;
      i++;
   }
   return(1);
}

int is_config_line(char *line)
{
   int i;

   i = 0;
   while (ft_isspace(line[i]))
      i++;
   if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
      return (1);
   if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
      return (1);
   if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
      return (1);
   if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
      return (1);
   if (line[i] == 'C' && ft_isspace(line[i + 1]))
      return (1);
   if (line[i] == 'F' && ft_isspace(line[i + 1]))
      return (1);
   return (0);
}

void parse_config(t_config *config, char *line)
{
   int i;

   i = 0;
   while (ft_isspace(line[i]))
     i++;
   if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(line[2]))
      config->no_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(line[2]))
      config->ea_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(line[2]))
      config->we_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isspace(line[2]))
      config->so_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (line[i] == 'C' && ft_isspace(line[i + 1]))
      config->ceiling = ft_strdup(ft_skip_spaces(&line[i + 1]));
   else if (line[i] == 'F' && ft_isspace(line[i + 1]))
      config->floor = ft_strdup(ft_skip_spaces(&line[i + 1]));
}

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

