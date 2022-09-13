/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:59:22 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/13 15:11:00 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	floor_casting(t_core *core);
static void	ray_start(t_core *core, int x);
static void	calculate_step(t_core *core);
static void	calculate_distance(t_core *core);
static void	draw_line(t_core *core, int x);

/* Creates a ray per pixel column in the screen, shot from the player,
 * calculating the distance towards the closest wall in front of it,
 * then draws a vertical line in the corresponding pixel column
 * depending on that distance to simulate a 3d environment.
 */
void	raycaster(t_core *core)
{
	int	x;

	floor_casting(core);
	x = 0;
	while (x < WIN_W)
	{
		ray_start(core, x);
		calculate_step(core);
		calculate_distance(core);
		draw_line(core, x);
		x++;
	}
}

static void	floor_casting(t_core *core)
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

/* Takes the initial position and direction of the ray in the map, and
 * the square it belongs to, then calculates the distance when the ray
 * crosses over to the next square in both, x and y, axis.
 */
static void	ray_start(t_core *core, int x)
{
	core->ray.camera_x = 2 * (double)x / (double)WIN_W - 1;
	core->ray.dir.x = core->player.dir.x + core->player.plane.x
		* core->ray.camera_x;
	core->ray.dir.y = core->player.dir.y + core->player.plane.y
		* core->ray.camera_x;
	core->ray.map_pos.x = (int)core->player.pos.x;
	core->ray.map_pos.y = (int)core->player.pos.y;
	if (core->ray.dir.x == 0)
		core->ray.delta_dis.x = pow(1, 30);
	else
		core->ray.delta_dis.x = fabs(1 / core->ray.dir.x);
	if (core->ray.dir.y == 0)
		core->ray.delta_dis.y = pow(1, 30);
	else
		core->ray.delta_dis.y = fabs(1 / core->ray.dir.y);
}

/* Calculates in which direction the ray will step forward
 * and the initial side distance of the ray.
 */
static void	calculate_step(t_core *core)
{
	if (core->ray.dir.x < 0)
	{
		core->ray.step.x = -1;
		core->ray.side_dis.x = (core->player.pos.x
				- core->ray.map_pos.x) * core->ray.delta_dis.x;
	}
	else
	{
		core->ray.step.x = 1;
		core->ray.side_dis.x = (core->ray.map_pos.x + 1.0
				- core->player.pos.x) * core->ray.delta_dis.x;
	}
	if (core->ray.dir.y < 0)
	{
		core->ray.step.y = -1;
		core->ray.side_dis.y = (core->player.pos.y
				- core->ray.map_pos.y) * core->ray.delta_dis.y;
	}
	else
	{
		core->ray.step.y = 1;
		core->ray.side_dis.y = (core->ray.map_pos.y + 1.0
				- core->player.pos.y) * core->ray.delta_dis.y;
	}
}

/* Using DDA, calculates if the ray jumps a step in x or y direction, and
 * stops when a wall is hit, then calculates the perpendicular distance
 * from the wall (Euclidean distance gives a fish-eye efffect).
 */
static void	calculate_distance(t_core *core)
{
	core->ray.hit = 0;
	while (core->ray.hit == 0)
	{
		if (core->ray.side_dis.x < core->ray.side_dis.y)
		{
			core->ray.side_dis.x += core->ray.delta_dis.x;
			core->ray.map_pos.x += core->ray.step.x;
			core->ray.face = 0;
		}
		else
		{
			core->ray.side_dis.y += core->ray.delta_dis.y;
			core->ray.map_pos.y += core->ray.step.y;
			core->ray.face = 1;
		}
		if (core->map.matrix[(int)core->ray.map_pos.y]
			[(int)core->ray.map_pos.x] > 0)
			core->ray.hit = 1;
	}
	if (core->ray.face == 0)
		core->ray.perp_wall_dis = core->ray.side_dis.x
			- core->ray.delta_dis.x;
	else
		core->ray.perp_wall_dis = core->ray.side_dis.y
			- core->ray.delta_dis.y;
}

/* Sets, depending on the distance to the wall, the height of the wall
 * on screen and what x coordinate of said wall was hit. Then calls a
 * function to dray this line with textures or flat colors.
 */
static void	draw_line(t_core *core, int x)
{
	if (core->ray.perp_wall_dis > 0.1)
		core->draw.height = (int)(WIN_H / core->ray.perp_wall_dis);
	else
		core->draw.height = 4 * WIN_H;
	core->draw.start = (-(core->draw.height)) / 2 + WIN_H / 2;
	core->draw.end = (core->draw.height) / 2 + WIN_H / 2;
	if (core->ray.face == 0)
		core->ray.wall_x = core->player.pos.y + core->ray.perp_wall_dis
			* core->ray.dir.y;
	else
		core->ray.wall_x = core->player.pos.x + core->ray.perp_wall_dis
			* core->ray.dir.x;
	core->ray.wall_x -= floor(core->ray.wall_x);
	if (core->is_textured == 0)
		draw_wall_flat(core, x);
	else
		draw_wall_textured(core, x);
}
