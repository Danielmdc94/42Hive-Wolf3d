/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:36:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/22 14:58:04 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	draw_row(t_core *core, t_floor *floor, int y);

/* Calculates leftmost and rightmost rays, then going row by row, gets the
 * distance from the 'camera' to the floor of the current pixel row.
 * it maps said pixel row to the chosen texture with draw_row()
 * Draws one full texture copy per cell on the floor
 */
void	floor_casting(t_core *core)
{
	int		y;
	int		y_relative;
	double	row_dis;
	t_floor	floor;

	floor.ray_dir0.x = core->player.dir.x - core->player.plane.x;
	floor.ray_dir0.y = core->player.dir.y - core->player.plane.y;
	floor.ray_dir1.x = core->player.dir.x + core->player.plane.x;
	floor.ray_dir1.y = core->player.dir.y + core->player.plane.y;
	y = WIN_H / 2;
	while (y < WIN_H)
	{
		y_relative = y - WIN_H / 2;
		row_dis = (0.5 * WIN_H) / y_relative;
		floor.step.x = row_dis * (floor.ray_dir1.x - floor.ray_dir0.x) / WIN_W;
		floor.step.y = row_dis * (floor.ray_dir1.y - floor.ray_dir0.y) / WIN_W;
		floor.curr.x = core->player.pos.x + row_dis * floor.ray_dir0.x;
		floor.curr.y = core->player.pos.y + row_dis * floor.ray_dir0.y;
		draw_row(core, &floor, y);
		y++;
	}
}

static void	draw_row(t_core *core, t_floor *floor, int y)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		floor->cell.x = (int)(floor->curr.x);
		floor->cell.y = (int)(floor->curr.y);
		floor->tex_x = (int)(core->textures.wood->w
				* (floor->curr.x - floor->cell.x))
			& (core->textures.wood->w - 1);
		floor->tex_y = (int)(core->textures.wood->h
				* (floor->curr.y - floor->cell.y))
			& (core->textures.wood->h - 1);
		floor->curr.x += floor->step.x;
		floor->curr.y += floor->step.y;
		set_pixel(core->sdl.screen, x, y,
			get_pixel(core->textures.greystone,
				floor->tex_x, floor->tex_y));
		x++;
	}
}
