/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:36:03 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/02 23:42:49 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*s2;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	s2 = (char *)malloc((end - start + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (start < end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}
/*
int	main(void)
{
	char chaine[] = "    HELLO, connard   ";
	char set[] = " ";
	char *result = ft_strtrim(chaine, set);

	printf("Apres trim, str vaut: %s\n", result);
	printf("Apres trim, str vaut: %zu\n", ft_strlen(result));

	free(result);
	return (0);
	// s2 = ft_substr(s1, start, end - start);
}*/