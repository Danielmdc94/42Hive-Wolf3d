/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:52:15 by dpalacio          #+#    #+#             */
/*   Updated: 2021/12/09 17:45:03 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

static void	free_ptr(char **dst, int j)
{
	while (j-- >= 0)
	{
		free(dst[j]);
	}
	free(dst);
}

static char	**cpy_dst(char **dst, char const *s, char c, int elem)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = -1;
	while (++j < elem)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		dst[j] = ft_strsub(s, start, i - start);
		if (!dst[j])
		{
			free_ptr(dst, j);
			return (NULL);
		}
		i++;
	}
	return (dst);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**dst;
	int		elem;

	if (s == NULL || !c)
		return (NULL);
	elem = ft_count_words(s, c);
	dst = (char **)ft_memalloc(sizeof(char *) * (elem + 1));
	if (dst == NULL)
		return (NULL);
	return (cpy_dst(dst, s, c, elem));
}
