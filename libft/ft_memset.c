/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:37:31 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/04 19:10:58 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t size)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	unsigned char ptr[] = "Bilal la terreur";
    printf("Avant ptr vaut: %s\n", ptr);
	ft_memset(ptr, 'B', 5);
	printf("Apres ptr vaut: %s", ptr);
	return (0);
}*/