/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:48:18 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/24 17:33:56 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	len_haystack;
	int		limit;
	int		n;

	len_needle = ft_strlen(needle);
	len_haystack = ft_strlen(haystack);
	limit = len - len_needle;
	n = 0;
	if (len_needle > len_haystack)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (len-- && *haystack != '\0')
	{
		if (n <= limit
			&& ft_memcmp((char *)haystack, (char *)needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
		n++;
	}
	return (NULL);
}
