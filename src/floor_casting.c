/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:36:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/16 13:42:43 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"


void	floor_casting(t_core *core)
{
	int		y;
	int		x;
	int		curr_pos;
	double	z;
	double	row_dis;
	t_floor	floor;

	y = WIN_H / 2;
	while (y < WIN_H)
	{
		floor.ray_dir0.x = core->player.dir.x - core->player.plane.x;
		floor.ray_dir0.y = core->player.dir.y - core->player.plane.y;
		floor.ray_dir1.x = core->player.dir.x + core->player.plane.x;
		floor.ray_dir1.y = core->player.dir.y + core->player.plane.y;
		curr_pos = y - WIN_H / 2;
		z = 0.5 * WIN_H;
		row_dis = z / curr_pos;
		floor.step.x = row_dis * (floor.ray_dir1.x - floor.ray_dir0.x) / WIN_W;
		floor.step.y = row_dis * (floor.ray_dir1.y - floor.ray_dir0.y) / WIN_W;
		floor.curr.x = core->player.pos.x + row_dis * floor.ray_dir0.x;
		floor.curr.y = core->player.pos.y + row_dis * floor.ray_dir0.y;
		while (x < WIN_W)
		{
			floor.cell.x = (int)(floor.curr.x);
			floor.cell.y = (int)(floor.curr.y);
			floor.tex_x = (int)(core->textures.wood->w * (floor.curr.x - floor.cell.x)) & (core->textures.wood->w - 1);
			floor.tex_y = (int)(core->textures.wood->h * (floor.curr.y - floor.cell.y)) & (core->textures.wood->h - 1);
			floor.curr.x += floor.step.x;
			floor.curr.y += floor.step.y;
			set_pixel(core->sdl.screen, x, y, get_pixel(core->textures.greystone, floor.tex_x, floor.tex_y));
			x++;
		}
		x = 0;
		y++;
	}
}
