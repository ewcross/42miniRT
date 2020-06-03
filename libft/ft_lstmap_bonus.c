/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:59:09 by ecross            #+#    #+#             */
/*   Updated: 2019/10/18 14:55:53 by ecross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*make_new_elem(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list*)malloc(sizeof(t_list));
	if (new_elem)
	{
		new_elem->content = content;
		new_elem->next = NULL;
	}
	return (new_elem);
}

static void		push_back(t_list **alst, t_list *new)
{
	t_list *temp;

	if (alst == NULL)
		return ;
	temp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (temp)
	{
		if (temp->next == NULL)
		{
			temp->next = new;
			return ;
		}
		temp = temp->next;
	}
}

static void		clean_list(t_list **lst, void (*del)(void *))
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

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *))
{
	void	*new_content;
	t_list	*new_elem;
	t_list	*new_list;

	new_list = NULL;
	if (f == NULL || del == NULL)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_elem = make_new_elem(new_content);
		if (!new_elem)
		{
			clean_list(&new_list, del);
			return (NULL);
		}
		push_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
