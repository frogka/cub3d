/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:24:19 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/04 19:10:38 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*
int	main(void)
{
	t_list	*list;
	t_list	*new;

	list = ft_lstnew("Hello World!");
	new = ft_lstnew("Bonjour le monde!");
	ft_lstadd_front(&list, new);
	printf("%s\n", (char *)list->content);
	printf("%s\n", (char *)list->next->content);
	return (0);
}*/