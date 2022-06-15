/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:46:51 by dpalacio          #+#    #+#             */
/*   Updated: 2021/12/06 13:27:31 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*crnt;

	if (!alst || !new)
		return ;
	crnt = *alst;
	while (crnt->next)
		crnt = crnt->next;
	crnt->next = new;
}
