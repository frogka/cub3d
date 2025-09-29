/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:39:24 by jdutille          #+#    #+#             */
/*   Updated: 2024/10/30 20:03:07 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	size_t			i;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (ch == s[i])
			return ((char *)&s[i]);
		i--;
	}
	if (ch == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char	*str = "aello, World!";
	int			ch;
	char		*result;

	ch = '\0';
	result = ft_strrchr(str, ch);
	printf("Le caractère '%s'", result);
}
// premier while s[i] pr parcourir tout les char de s*/