#include "../include/wolf3d.h"

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
		core->ray.map_pos.y = (int)core->player.pos.y;
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
		SDL_SetRenderDrawColor(core->sdl.rend, core->draw.color - core->ray.perp_wall_dis * 5,
				core->draw.color - core->ray.perp_wall_dis * 5, core->draw.color - core->ray.perp_wall_dis * 5, 255);
		SDL_RenderDrawLine(core->sdl.rend, x, core->draw.start,
				x, core->draw.end);
		SDL_SetRenderDrawColor(core->sdl.rend, 90, 100, 100, 255);
		SDL_RenderDrawLine(core->sdl.rend, x, core->draw.end + 1,
				x, WIN_H - 1);
		//------
		if (x)
		{
			SDL_SetRenderDrawColor(core->sdl.rend, 0, 150, 0, 155);
			SDL_RenderDrawLine(core->sdl.rend, 
			WIN_W - 10 * core->map.width + (core->player.pos.x * 10), 
			(core->player.pos.y * 10), 
			WIN_W - 10 * core->map.width + (core->player.pos.x * 10) + core->ray.dir.x * core->ray.perp_wall_dis * 10, 
			(core->player.pos.y * 10) + core->ray.dir.y * core->ray.perp_wall_dis * 10);
			printf("\nRAY	WALL DISTANCE	FACE	DIR.X		DIR.Y		MAP.X		MAP.Y		STEP.X		STEP.Y		DELTA.X		DELTA.Y		SIDE.X		SIDE.Y\n%d	%f	%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f", x,
				core->ray.perp_wall_dis, core->ray.face, core->ray.dir.x, core->ray.dir.y, core->ray.map_pos.x,
				core->ray.map_pos.y, core->ray.step.x, core->ray.step.y, core->ray.delta_dis.x, core->ray.delta_dis.y,
				core->ray.side_dis.x, core->ray.side_dis.y);
		}
		//------
		x++;
	}
}
