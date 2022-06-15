/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:02:16 by dpalacio          #+#    #+#             */
/*   Updated: 2021/12/06 16:46:24 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = (*f)(lst);
	if (lst->next)
	{
		new->next = ft_lstmap(lst->next, (*f));
		if (!new->next)
		{
			free(new->content);
			free(new);
			return (NULL);
		}
	}
	return (new);
}
