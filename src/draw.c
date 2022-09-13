/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:17:39 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/13 11:51:58 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	draw_wall_textured(t_core *core, int x)
{
	int			tex_x;
	int			tex_y;
	double		step;
	int			y;
	double		tex_pos;

	tex_x = (int)(core->ray.wall_x * (double)(core->textures.wood->w));
	if (core->ray.face == 0 && core->ray.dir.x > 0)
		tex_x = core->textures.wood->w - tex_x - 1;
	if (core->ray.face == 1 && core->ray.dir.y < 0)
		tex_x = core->textures.wood->w - tex_x - 1;
	step = 1.0 * (core->textures.wood->h) / core->draw.height;
	tex_pos = (core->draw.start - WIN_H / 2 + core->draw.height / 2) * step;
	y = core->draw.start;
	while (y++ <= core->draw.end)
	{
		tex_y = (int)tex_pos & (core->textures.wood->h - 1);
		tex_pos += step;
		set_pixel(core->sdl.screen, x, y,
			get_pixel(choose_texture(core), tex_x, tex_y));
	}
//	while (y++ <= WIN_H)
//		set_pixel(core->sdl.screen, x, y - 1, 0x5a6464);
}

SDL_Surface	*choose_texture(t_core *core)
{
	if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 1)
		return (core->textures.greystone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 2)
		return (core->textures.colorstone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 3)
		return (core->textures.bluestone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 4)
		return (core->textures.redbrick);
	else
		return (core->textures.wood);
}

void	draw_wall_flat(t_core *core, int x)
{
	int	y;

	y = core->draw.start;
	while (y <= core->draw.end)
	{
		if (core->ray.face == 0)
			set_pixel(core->sdl.screen, x, y, 0xc8c8c8);
		else
			set_pixel(core->sdl.screen, x, y, 0x969696);
		y++;
	}
	while (y++ < WIN_H)
		set_pixel(core->sdl.screen, x, y - 1, 0x5a6464);
}
