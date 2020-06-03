/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:38:12 by ecross            #+#    #+#             */
/*   Updated: 2019/10/16 19:16:53 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *store;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		store = *lst;
		*lst = (*lst)->next;
		free(store);
	}
}
