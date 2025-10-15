/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:44:27 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/15 18:13:55 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extraction(int fd, char *stock)
{
	char	*buf;
	char	*tmp;
	ssize_t	fd_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	fd_read = 1;
	while (!ft_strchr(stock, '\n') && fd_read != 0)
	{
		fd_read = read(fd, buf, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(buf);
			free(stock);
			return (NULL);
		}
		buf[fd_read] = '\0';
		tmp = stock;
		stock = ft_strjoin(stock, buf);
		free(tmp);
	}
	free(buf);
	return (stock);
}

char	*print_line(char *stock)
{
	char	*new_line;
	int		j;

	j = 0;
	if (!stock[j])
		return (NULL);
	while (stock[j] != '\n' && stock[j] != '\0')
		j++;
	new_line = (char *)malloc((j + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	j = 0;
	while (stock[j] != '\n' && stock[j] != '\0')
	{
		new_line[j] = stock[j];
		j++;
	}
	if (stock[j] == '\n')
	{
		new_line[j] = '\n';
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*reste(char *stock)
{
	char	*reste;
	int		j;
	int		i;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	reste = (char *)malloc((ft_strlen(stock) - i + 1) * sizeof(char));
	if (!reste)
		return (NULL);
	j = 0;
	i++;
	while (stock[i])
	{
		reste[j++] = stock[i++];
	}
	reste[j] = '\0';
	free(stock);
	return (reste);
}

char	*get_next_line(int fd)
{
	static char	*stock[FD_SIZE];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_SIZE < 0 || fd > FD_SIZE)
		return (NULL);
	stock[fd] = extraction(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	line = print_line(stock[fd]);
	tmp = reste(stock[fd]);
	if (!tmp)
		stock[fd] = NULL;
	else
		stock[fd] = tmp;
	return (line);
}
