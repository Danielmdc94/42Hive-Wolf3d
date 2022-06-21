/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/21 18:37:00 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render_frame(t_core *core)
{
	SDL_SetRenderDrawColor(core->sdl.rend, 25, 25, 25, 255);
	SDL_RenderClear(core->sdl.rend);
	core->frames.old_time = core->frames.time;
	core->frames.time = clock();
	core->frames.frame_time = (core->frames.time - core->frames.old_time)
		/ CLOCKS_PER_SEC;
//	core->frames.fps = 1.0 / core->frames.frame_time;
//	SDL_Delay(1000 / 60 - core->frames.frame_time / 1000);
	core->player.move_speed = core->frames.frame_time * 20;
	core->player.rot_speed = core->frames.frame_time * 12;
//-------
	printf("%f\n", core->frames.fps);
//-------
	raycaster(core);
	render_map(core);
	SDL_RenderPresent(core->sdl.rend);
}

void	raycaster(t_core *core)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		//ray position in screen and direction
		core->ray.camera_x = 2 * (double)x / (double)WIN_W - 1;
		core->ray.dir.x = core->player.dir.x + core->player.plane.x
			* core->ray.camera_x;
		core->ray.dir.y = core->player.dir.y + core->player.plane.y
			* core->ray.camera_x;
		//what square the payer is on the map
		core->ray.map_pos.x = (int)core->player.pos.x;
		core->ray.map_pos.y = (int)core->player.dir.y;
		//length of ray to the next x and y sides of a square indepenently
		if (core->ray.dir.x == 0)
			core->ray.delta_dis.x = pow(1, 30);
		else
			core->ray.delta_dis.x = fabs(1 / core->ray.dir.x);
		if (core->ray.dir.y == 0)
			core->ray.delta_dis.y = pow(1, 30);
		else
			core->ray.delta_dis.y = fabs(1 / core->ray.dir.y);
		//calculate step and first ray.side_dist
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
		//DDA to jump to nex square, either on x or y direction until square is a wall
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
			{
				core->ray.hit = 1;
			}
		}
		//Perpendicular distance from camera to wall (normal distance makes fisheye efect)
		if (core->ray.face == 0)
			core->ray.perp_wall_dis = core->ray.side_dis.x
				- core->ray.delta_dis.x;
		else
			core->ray.perp_wall_dis = core->ray.side_dis.y
				- core->ray.delta_dis.y;
		//heigth of line to draw, starting and ending pixel for the line
		core->draw.height = (int)(WIN_H / core->ray.perp_wall_dis);
		core->draw.start = (-(core->draw.height)) / 2 + WIN_H / 2;
		if (core->draw.start < 0)
			core->draw.start = 0;
		core->draw.end = (core->draw.height) / 2 + WIN_H / 2;
		if (core->draw.end >= WIN_H)
			core->draw.end = WIN_H - 1;
		//Choose color for the wall
		if (core->ray.face == 0)
			core->draw.color = 200;
		else
			core->draw.color = 150;
		//draw the line
		SDL_SetRenderDrawColor(core->sdl.rend, core->draw.color,
				core->draw.color, core->draw.color, 255);
		SDL_RenderDrawLine(core->sdl.rend, x, core->draw.start,
				x, core->draw.end);
		SDL_SetRenderDrawColor(core->sdl.rend, 90, 100, 100, 255);
		SDL_RenderDrawLine(core->sdl.rend, x, core->draw.end + 1,
				x, WIN_H - 1);
		//------
		if (x == 480)
		{
			SDL_SetRenderDrawColor(core->sdl.rend, 0, 150, 0, 155);
			SDL_RenderDrawLine(core->sdl.rend, 
			WIN_W - 10 * core->map.width + (core->player.pos.x * 10), 
			(core->player.pos.y * 10), 
			WIN_W - 10 * core->map.width + (core->player.pos.x * 10) + core->ray.dir.x * core->ray.perp_wall_dis * 10, 
			(core->player.pos.y * 10) + core->ray.dir.y * core->ray.perp_wall_dis * 10);
			printf("\nRAY	WALL DISTANCE	FACE	DIR.X		DIR.Y		MAP.X		MAP.Y		DELTA.X		DELTA.Y		SIDE.X		SIDE.Y\n%d	%f	%d	%f	%f	%f	%f	%f	%f	%f	%f", x, core->ray.perp_wall_dis, core->ray.face, core->ray.dir.x, core->ray.dir.y,
				core->ray.map_pos.x, core->ray.map_pos.y, core->ray.delta_dis.x, core->ray.delta_dis.y, core->ray.side_dis.x, core->ray.side_dis.y);
		}
		//------
		x++;
	}
}

 void    render_map(t_core *core)
{
	SDL_Rect minimap;
	SDL_Rect wall;
	SDL_Rect player;
	int x;
	int y;
	
	minimap.x = WIN_W - 10 * core->map.width;
	minimap.y = 0;
	minimap.w = 10 * core->map.width - 1;
	minimap.h = 10 * core->map.height - 1;
	wall.w = 10;
	wall.h = 10;
	player.x = minimap.x + (int)(core->player.pos.x * 10) - 2;
	player.y = minimap.y + (int)(core->player.pos.y * 10) - 2;
	player.w = 5;
	player.h = 5;
	x = 0;
	y = 0;
	SDL_SetRenderDrawColor(core->sdl.rend, 100, 100, 100, 150);
	SDL_RenderDrawRect(core->sdl.rend, &minimap);
	while (y < core->map.height)
	{
		while (x < core->map.width)
		{
			if (core->map.matrix[y][x] != 0)
			{
				wall.x = minimap.x + x * 10;
				wall.y = minimap.y + y * 10;
				SDL_RenderDrawRect(core->sdl.rend, &wall);
				SDL_RenderFillRect(core->sdl.rend, &wall);
			}
			x++;
		}
		x = 0;
		y++;
	}
	SDL_SetRenderDrawColor(core->sdl.rend, 250, 250, 0, 150);
	SDL_RenderDrawRect(core->sdl.rend, &player);
	SDL_RenderDrawLine(core->sdl.rend, minimap.x + (int)(core->player.pos.x * 10), minimap.y + (int)(core->player.pos.y * 10), minimap.x + (int)(core->player.pos.x * 10) + core->player.dir.x * 6, minimap.y + (int)(core->player.pos.y * 10) + core->player.dir.y * 8);
}
