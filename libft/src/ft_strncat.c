/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:35:42 by dpalacio          #+#    #+#             */
/*   Updated: 2021/11/24 17:31:42 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;
	size_t	atmost;

	s = s1;
	if (n > ft_strlen(s2))
		atmost = ft_strlen(s2);
	else
		atmost = n;
	s += ft_strlen(s1);
	ft_memcpy (s, s2, atmost);
	s[atmost] = '\0';
	return (s1);
}
