/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:58:16 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/04 19:10:52 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (n--)
	{
		if ((char)c == ptr[i])
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char str[] = "Hello, world!";
	char *result;
	int n = 2;

	result = ft_memchr(str, 'w', n);
	if (result != NULL)
		printf("Character found: %c trouver a %ld\n", *result);
	else
		printf("Character not found\n");

	return (0);
}*/