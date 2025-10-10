/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:46 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/10 19:41:31 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_map_lines(int fd, t_map *map)
{
   char *line;
   int len;
   int count;

   len = 0;
   count = 0;
   while ((line = get_next_line(fd)) != NULL)
   {
      if (is_map_line(line))
      {
         count++;
         len = ft_strlen(line);
         printf("%d\n", len);
         if (len > map->width)
            map->width = len;
         free(line);
      }
      else
         free(line);
   }
   map->height = count;
   return (count);
}
char **fill_map(int fd, t_map *map)
{
   int i;
   int j;
   char *line;
   char **grid;

   printf("1width = %d, height = %d\n", map->width, map->height);
   grid = malloc(sizeof(char *) * (map->height + 1));
   if (!grid)
      return(NULL);
   i = 0;
   while ((line = get_next_line(fd)) != NULL)
   {
      if (line[ft_strlen(line) - 1] == '\n')
         line[ft_strlen(line) - 1] = '\0';
      if (is_map_line(line))
      {
         grid[i] = ft_strdup(line);
         is_one_player(map, line);
         i++;
      }
      free(line);
   }
   grid[i] = NULL;
   if (map->player_found != 1)
   {
      printf("Nombre de joueurs %d\n", map->player_found);
      printf("Erreur nombres de joueurs\n");
      exit(-1);
      //stope le programem pour void player position
      //fonciton qui free grid; 
   }
   printf("2width = %d, height = %d\n", map->width, map->height);
   printf("%s\n", grid[i]);
   j = 0;
   while (grid[j])
   {
      printf("%s\n", grid[j]);
      printf("%zu\n", ft_strlen(grid[j]));
      j++;
   }
   return(grid);
}

//pbl qunas joeur est a l'extremite +P quand la lettre est != du joueur
int is_map_line(char *line)
{
   int i;

   i = 0;
   while (line[i] && line[i] != '\0')
   {
      if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
      {
         printf("Caractere non valable\n");
         return (0);
         //fonction pour free grid et line et quitter le programme;
      }
      i++;
   }
   return(1);
}

//fonction qui check la validite des config
int is_config_line(char *line)
{
   int i;

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
   //else
   //   return; //message d'erreur 
   return (0);
}

//fonction qui atttribut les config a la structure
// ajout d'un char temporaire ??
void parse_config(t_config *config, char *line)
{
   int i;

   i = 0;
   while (ft_isspace(&line[i]))
     i++;
   if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(&line[i + 2]))
      config->no_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(&line[i + 2]))
      config->ea_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(&line[i + 2]))
      config->we_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isspace(&line[i + 2]))
      config->so_text = ft_strdup(ft_skip_spaces(&line[i + 2]));
   else if (line[i] == 'C' && ft_isspace(&line[i + 1]))
      config->ceiling = check_colors(ft_skip_spaces(&line[i + 1]));
   else if (line[i] == 'F' && ft_isspace(&line[i + 1]))
      config->floor = check_colors(ft_skip_spaces(&line[i + 1]));
}

//faire une focntin qui check tout le .cub et qui appelle les fonctions annexes
//a chque etapes
//1er check que les configs sont valides
//si valide alors attributs aux structures
//sinon message d'erreur

int	xrgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int check_colors(char *line)
{
   char **colors;
   int r;
   int g;
   int b;
   int i;

   i = 0;
   colors = ft_split(line, ',');
   while (colors[i])
      i++;
   if (i != 3)
   {
      free_split(colors);
      return(-1);
   }
   r = ft_atoi(colors[0]);
   g = ft_atoi(colors[1]);
   b = ft_atoi(colors[2]);
   free_split(colors);
   if (check_valid_numbers(r, g, b) == 1)
      return (xrgb(r, g, b));
   return (-1);
   //message d'erreur sur la validite des nombres
}

int check_valid_numbers(int r, int g, int b)
{
   if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
      return(0);
   return (1);
}




void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp
				/ 8));
	*(unsigned int *)dst = color;
}



int main ()
{
   int fd;
   //char *line;
   t_data data;
   t_map *map;

   //line = NULL;
   map = malloc(sizeof(t_map));
   map->height = 0;
   map->width = 0;
   map->player_found = 0;
   data.map = map;
   printf("map addr main = %p\n", map);
   if (!map) 
      exit(1);
      //faire une condition qui ouvre seulement si .cub
   fd = open("map.cub", O_RDONLY);
      // printf("after open: fd = %d\n", fd);
      // while ((line = get_next_line(fd)))
      // {
         //    printf("%s\n", line);
         //    if (is_map_line(line))
         //    {
            //       free(line);
            //       break;
            //    }
            //    free(line);
            // }
   count_map_lines(fd, map);
   printf("width = %d, height = %d\n", map->width, map->height);
   close(fd);
   fd = open("map.cub", O_RDONLY);
   //fill_map(fd, map);
   map->grid = fill_map(fd, map);
   if (!map->grid)
   {
      perror("fill_map failed");
      return (1);   
   }
   if (player_position(map))
   {
      printf("MANGE T MORTS\n");
      return (1);
   }
   printf("%lf\n", map->player_x);
   printf("%lf\n", map->player_y);
   printf("%lf\n", map->player_dir);
   printf("adresse data = %p\n", &data);
   printf("adresse map  = %p\n", data.map);
   data.mlx_ptr = mlx_init();
   data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT
      , "test");
   data.img.img_ptr = mlx_new_image(data.mlx_ptr , WIDTH, HEIGHT);
   printf("FGASDFSDF\n");
data.img.addr = mlx_get_data_addr(data.img.img_ptr , &data.img.bpp, &data.img.line_len, &data.img.endian);
draw_map(map, &data);
mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);
init_hook(&data);
mlx_loop(data.mlx_ptr);
return (0);
}

