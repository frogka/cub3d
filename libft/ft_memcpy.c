/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:10:06 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/02 23:38:19 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int	main(void) {
	char src[] = "Hello, World!";
	char dst[20];

	// Appel à ft_memcpy
	ft_memcpy(dst, src, sizeof(src));

	// Affichage du résultat
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dst);

	return (0);
}
// if (dst == (void *)0 && src == (void *)0)*/