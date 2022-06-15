/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:43:48 by dpalacio          #+#    #+#             */
/*   Updated: 2022/01/20 15:24:21 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*dst;

	if (s == NULL)
		return (NULL);
	len = ft_strlen (s);
	dst = (char *)ft_memalloc(len + 1);
	if (dst == NULL)
		return (NULL);
	while (--len >= 0)
		dst[len] = f(len, s[len]);
	return (dst);
}
