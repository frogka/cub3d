/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:03:45 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/02 17:43:58 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	o;
	size_t			i;

	i = 0;
	o = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == o)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == o)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char *str = "Hello, World!";
	int ch = 'o';
	char *result = ft_strchr(str, ch);

	printf("Le caractère '%s'", result);
}*/