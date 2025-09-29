/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:00:18 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/04 01:00:57 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*
int	main(void)
{
	t_list	*list;
	t_list	*new;

	list = ft_lstnew("Hello World!");
	new = ft_lstnew("Bonjour le monde!");
	ft_lstadd_front(&list, new);
	printf("%d\n", ft_lstsize(list));
	return (0);
}*/