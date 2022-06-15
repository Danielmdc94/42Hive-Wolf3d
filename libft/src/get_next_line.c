/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:42:43 by dpalacio          #+#    #+#             */
/*   Updated: 2022/01/18 15:52:37 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	save_line(char **placeholder, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*placeholder)[i] != '\n' && (*placeholder)[i] != '\0')
		i++;
	if ((*placeholder)[i] == '\n')
	{
		*line = ft_strsub((*placeholder), 0, i);
		temp = ft_strdup(&((*placeholder)[i + 1]));
		free(*placeholder);
		*placeholder = temp;
		if ((*placeholder)[0] == '\0')
			ft_memdel((void **)placeholder);
	}
	else
	{
		*line = ft_strdup(*placeholder);
		ft_memdel((void **)placeholder);
	}
	return (1);
}

static int	return_values(char **placeholder, ssize_t buff_len, char **line)
{
	if (buff_len == 0 && (*placeholder == NULL || !ft_strlen(*placeholder)))
	{
		ft_memdel((void **)placeholder);
		return (0);
	}
	else if (buff_len < 0)
	{
		ft_memdel((void **)placeholder);
		return (-1);
	}
	else
		return (save_line(placeholder, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*placeholder[FD_MAX];
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	ssize_t		buff_len;

	if (fd < 0 || fd > FD_MAX || !line)
		return (-1);
	buff_len = read(fd, buff, BUFF_SIZE);
	while (buff_len > 0)
	{
		buff[buff_len] = '\0';
		if (!placeholder[fd])
			placeholder[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(placeholder[fd], buff);
			free(placeholder[fd]);
			placeholder[fd] = temp;
		}
		if (ft_strchr(placeholder[fd], '\n'))
			break ;
		buff_len = read(fd, buff, BUFF_SIZE);
	}
	return (return_values(&placeholder[fd], buff_len, line));
}
