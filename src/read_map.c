/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:29:05 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/26 12:17:32 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	get_width(t_core *core, char *line);
static void	allocate_map(t_core *core);
static void	fill_map_matrix(t_core *core, int fd);
static void	fill_matrix_line(t_core *core, char **line_array, int y);

/* Reads and copies the  given map into the core structure
 */
void	read_map(t_core *core)
{
	char	*line;
	int		fd;

	fd = open(core->map.file, O_RDONLY);
	if (fd < 0)
		error_print(core, "Error: Failed to open map file");
	core->map.height = 0;
	while (get_next_line(fd, &line) == 1)
	{
		get_width(core, line);
		core->map.height++;
		free(line);
	}
	close(fd);
	if (core->map.height == 0)
		error_print(core, "Error: Invalid file");
	allocate_map(core);
	fd = open(core->map.file, O_RDONLY);
	if (fd < 0)
		error_print(core, "Error: Failed to open map file");
	fill_map_matrix(core, fd);
	close(fd);
	if (core->map.width < 5 || core->map.height < 5)
		error_print(core, "Error: Map is too small");
}

static void	get_width(t_core *core, char *line)
{
	int	width;
	int	inside;
	int	i;

	width = 0;
	inside = 0;
	i = -1;
	while (line[++i])
	{
		if (inside && line[i] == ' ')
			inside = 0;
		if (!inside && line[i] != ' ')
		{
			inside = 1;
			width++;
		}
	}
	if (core->map.height == 0)
		core->map.width = width;
	else if (core->map.width != width)
		error_print(core, "Error: Invalid map");
	if (core->map.width == 0)
		error_print(core, "Error: Invalid file");
}

static void	allocate_map(t_core *core)
{
	int	i;

	i = 0;
	core->map.matrix = (int **)ft_memalloc((core->map.height) * sizeof(int *));
	if (!core->map.matrix)
		error_print(core, "Error: Failed to allocate map matrix");
	while (i < core->map.height)
	{
		core->map.matrix[i] = (int *)ft_memalloc(core->map.width * sizeof(int));
		if (!core->map.matrix[i])
			error_print(core, "Error: Failed to allocate map matrix");
		i++;
	}
}

static void	fill_map_matrix(t_core *core, int fd)
{
	char	**line_array;
	char	*line;
	int		y;
	int		i;

	y = 0;
	i = -1;
	while (get_next_line(fd, &line) == 1)
	{
		line_array = ft_strsplit(line, ' ');
		fill_matrix_line(core, line_array, y);
		while (i++ < core->map.width)
			free(line_array[i]);
		i = -1;
		free(line_array);
		free(line);
		y++;
	}
}

static void	fill_matrix_line(t_core *core, char **line_array, int y)
{
	int	x;

	x = 0;
	while (line_array[x] != NULL)
	{
		core->map.matrix[y][x] = ft_atoi(line_array[x]);
		x++;
	}
}
