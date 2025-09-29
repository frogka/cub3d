/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:32:44 by jdutille          #+#    #+#             */
/*   Updated: 2024/11/04 19:10:39 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nul;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		nul = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nul;
	}
	free(*lst);
	*lst = NULL;
}
