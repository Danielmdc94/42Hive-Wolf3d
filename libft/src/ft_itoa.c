/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:43:12 by dpalacio          #+#    #+#             */
/*   Updated: 2021/12/02 22:13:30 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_chr(long x)
{
	int	i;

	i = 1;
	while (x > 9 || x < -9)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

static char	*cpy_digits(char *nbr, int n, int i)
{
	int	x;

	nbr[i] = '\0';
	if (n < 0)
		nbr[0] = '-';
	if (n == -2147483648)
	{
		nbr[1] = '2';
		n = 147483648;
	}
	x = (ft_abs(n));
	while (x > 9)
	{
		nbr[i - 1] = (x % 10) + '0';
		x = x / 10;
		i--;
	}
	nbr[i - 1] = x + '0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		i;

	i = count_chr(n);
	if (n < 0)
		i++;
	nbr = (char *)ft_memalloc(sizeof(char) * (i + 1));
	if (nbr == NULL)
		return (NULL);
	return (cpy_digits(nbr, n, i));
}
