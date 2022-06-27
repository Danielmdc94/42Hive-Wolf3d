/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:56:40 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/27 20:56:36 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	on_keydown(t_core *core);
static void	move(t_core *core);
static void	rotate(t_core *core);

void	controls(t_core *core)
{
	if (core->sdl.event.type == SDL_QUIT)
		core->is_runing = 0;
	if (core->sdl.event.type == SDL_KEYDOWN)
		on_keydown(core);
}

static void	on_keydown(t_core *core)
{
	if (core->sdl.event.key.keysym.sym == SDLK_w
		|| core->sdl.event.key.keysym.sym == SDLK_s)
		move(core);
	if (core->sdl.event.key.keysym.sym == SDLK_a
		|| core->sdl.event.key.keysym.sym == SDLK_d)
		rotate(core);
	if (core->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		core->is_runing = 0;
}

static void	move(t_core *core)
{
	if (core->sdl.event.key.keysym.sym == SDLK_w)
	{
		core->player.pos.x += core->player.dir.x * core->player.m_speed;
		core->player.pos.y += core->player.dir.y * core->player.m_speed;
	}
	if (core->sdl.event.key.keysym.sym == SDLK_s)
	{
		core->player.pos.x -= core->player.dir.x * core->player.m_speed;
		core->player.pos.y -= core->player.dir.y * core->player.m_speed;
	}
}

static void	rotate(t_core *core)
{
	core->temp.dir = core->player.dir.x;
	core->temp.plane = core->player.plane.x;
	if (core->sdl.event.key.keysym.sym == SDLK_a)
	{
		core->player.dir.x = core->player.dir.x * cos(-core->player.r_speed)
			- core->player.dir.y * sin(-core->player.r_speed);
		core->player.dir.y = core->temp.dir * sin(-core->player.r_speed)
			+ core->player.dir.y * cos(-core->player.r_speed);
		core->player.plane.x = core->player.plane.x * cos(-core->player.r_speed)
			- core->player.plane.y * sin(-core->player.r_speed);
		core->player.plane.y = core->temp.plane * sin(-core->player.r_speed)
			+ core->player.plane.y * cos(-core->player.r_speed);
	}
	if (core->sdl.event.key.keysym.sym == SDLK_d)
	{
		core->player.dir.x = core->player.dir.x * cos(core->player.r_speed)
			- core->player.dir.y * sin(core->player.r_speed);
		core->player.dir.y = core->temp.dir * sin(core->player.r_speed)
			+ core->player.dir.y * cos(core->player.r_speed);
		core->player.plane.x = core->player.plane.x * cos(core->player.r_speed)
			- core->player.plane.y * sin(core->player.r_speed);
		core->player.plane.y = core->temp.plane * sin(core->player.r_speed)
			+ core->player.plane.y * cos(core->player.r_speed);
	}
}
