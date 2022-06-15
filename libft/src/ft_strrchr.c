/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:00:33 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/22 16:05:28 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len;

	len = ft_strlen(s) + 1;
	if (!s)
		return (NULL);
	while (len--)
	{
		if (((unsigned char *)s)[len] == (unsigned char)c)
			return ((char *)s + len);
	}
	return (NULL);
}
