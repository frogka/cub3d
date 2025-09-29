/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:07:48 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/02 23:33:58 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_mots(char const *str, char c)
{
	int	mot;
	int	count;
	int	i;

	mot = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && mot == 0)
		{
			mot = 1;
			count++;
		}
		else if (str[i] == c)
		{
			mot = 0;
		}
		i++;
	}
	return (count);
}

static char	*char_mot(const char *str, size_t start, size_t end)
{
	size_t	i;
	char	*str1;
	size_t	len;

	i = 0;
	len = end - start;
	if (!str)
		return (NULL);
	str1 = (char *)malloc((len + 1) * sizeof(char));
	if (!str1)
		return (NULL);
	while (start < end)
	{
		str1[i++] = str[start++];
	}
	str1[i] = '\0';
	return (str1);
}

static void	*free_res(char **split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static char	**mfnorminette(char **res, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		end = i;
		if (start < end)
		{
			res[j] = char_mot(s, start, end);
			if (!(res[j]))
				return (free_res(res, j));
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((count_mots(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (mfnorminette(res, s, c));
}
/*
int	main(void)
{
	char **result;
	char *str = "Bonjour je suis Bilal alias Skeeter";
	char delimiter = ' ';

	result = ft_split(str, delimiter);

	if (!result)
	{
		printf("Erreur lors de la création du tableau de mots.\n");
		return (1);
	}

	// Affichage des mots
	for (int i = 0; result[i] != NULL; i++)
	{
		printf("Mots[%d]: %s\n", i, result[i]);
		free(result[i]); // N'oubliez pas de libérer la mémoire
	}

	free(result); // Libérer le tableau
	return (0);
}*/