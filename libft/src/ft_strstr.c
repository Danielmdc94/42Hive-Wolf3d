/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:59:53 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/23 14:10:51 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int	len_needle;
	unsigned int	len_haystack;

	len_needle = ft_strlen(needle);
	len_haystack = ft_strlen(haystack);
	if (len_needle > len_haystack)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		if (ft_strncmp((char *)haystack, (char *)needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
