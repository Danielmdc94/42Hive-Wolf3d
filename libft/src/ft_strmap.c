/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:08:46 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/25 16:51:20 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		len;
	char	*dst;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	dst = (char *)ft_memalloc(len + 1);
	if (dst == NULL)
		return (NULL);
	while (--len >= 0)
		dst[len] = f(s[len]);
	return (dst);
}
