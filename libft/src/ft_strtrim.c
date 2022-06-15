/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:28:44 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/29 16:47:48 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dst;
	size_t	i;
	size_t	len;
	size_t	start;
	size_t	end;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = 0;
	start = 0;
	end = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	start = i;
	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i > start)
		i--;
	end = i;
	len = end - start + 1;
	dst = ft_strsub(s, start, len);
	return (dst);
}
