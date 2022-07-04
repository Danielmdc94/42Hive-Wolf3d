/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:59:22 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/04 15:05:04 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

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

	x = 0;
	while (x < WIN_W)
	{
		ray_start(core, x);
		calculate_step(core);
		calculate_distance(core);
		draw_line(core, x);
		//------
		if (x)
		{
			SDL_SetRenderDrawColor(core->sdl.rend, 0, 150, 0, 155);
			SDL_RenderDrawLine(core->sdl.rend,
				WIN_W - 10 * core->map.width + (core->player.pos.x * 10),
				(core->player.pos.y * 10),
				WIN_W - 10 * core->map.width + (core->player.pos.x * 10)
				+ core->ray.dir.x * core->ray.perp_wall_dis * 10,
				(core->player.pos.y * 10) + core->ray.dir.y * core->ray.perp_wall_dis * 10);
/*			printf("\nRAY	WALL DISTANCE	FACE	DIR.X		DIR.Y		MAP.X		MAP.Y		STEP.X		STEP.Y		DELTA.X		DELTA.Y		SIDE.X		SIDE.Y\n%d	%f	%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f", x,
				core->ray.perp_wall_dis, core->ray.face, core->ray.dir.x, core->ray.dir.y, core->ray.map_pos.x,
				core->ray.map_pos.y, core->ray.step.x, core->ray.step.y, core->ray.delta_dis.x, core->ray.delta_dis.y,
				core->ray.side_dis.x, core->ray.side_dis.y);
		*/
		}
		x++;
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

/* Draws a vertical line, depending on the perpendicular distance of
 * the ray, on the corresponding pixel column.
 */
static void	draw_line(t_core *core, int x)
{
/*	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;
*/
	core->draw.height = (int)(WIN_H / core->ray.perp_wall_dis);
	core->draw.start = (-(core->draw.height)) / 2 + WIN_H / 2;
	if (core->draw.start < 0)
		core->draw.start = 0;
	core->draw.end = (core->draw.height) / 2 + WIN_H / 2;
	if (core->draw.end >= WIN_H)
		core->draw.end = WIN_H - 1;
	//--------
/*	if (core->ray.face == 0)
		wall_x = core->player.pos.y + core->ray.perp_wall_dis * core->ray.dir.y;
	else
		wall_x = core->player.pos.x + core->ray.perp_wall_dis * core->ray.dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(core->sdl.texture->w));
	if (core->ray.face == 0 && core->ray.dir.x > 0)
		tex_x = core->sdl.texture->w - tex_x - 1;
	if (core->ray.face == 1 && core->ray.dir.y < 0)
		tex_x = core->sdl.texture->w - tex_x - 1;
	step = 1.0 * core->sdl.texture->h / core->draw.height;
	tex_pos = (core->draw.start - WIN_H / 2 + core->draw.height / 2) * step;
	y = core->draw.start;
	while (y < core->draw.end)
	{
		tex_y = (int)tex_pos & (core->sdl.texture->h - 1);
		tex_pos += step;
		color = core->sdl.texture->pixels[core->sdl.texture->h * tex_y + tex_x];
		y++;
	}

*/	if (core->ray.face == 0)
		core->draw.color = 200;
	else
		core->draw.color = 150;
	SDL_SetRenderDrawColor(core->sdl.rend,
		core->draw.color - core->ray.perp_wall_dis * 5,
		core->draw.color - core->ray.perp_wall_dis * 5,
		core->draw.color - core->ray.perp_wall_dis * 5, 255);
	SDL_RenderDrawLine(core->sdl.rend, x, core->draw.start,
		x, core->draw.end);
	SDL_SetRenderDrawColor(core->sdl.rend, 90, 100, 100, 255);
	SDL_RenderDrawLine(core->sdl.rend, x, core->draw.end + 1,
		x, WIN_H - 1);
}
