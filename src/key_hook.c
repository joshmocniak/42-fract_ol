/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:33:18 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 03:40:52 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_xy(int keycode, t_vars *v)
{
	double		incr;

	incr = 1.0 / v->zoom_incr;
	if (keycode == 1 || keycode == 125)
	{
		if (v->move_y <= 200)
			v->move_y += incr;
	}
	else if (keycode == 13 || keycode == 126)
	{
		if (v->move_y >= -200)
			v->move_y -= incr;
	}
	if (keycode == 0 || keycode == 123)
	{
		if (v->move_x >= -200)
			v->move_x -= incr;
	}
	else if (keycode == 2 || keycode == 124)
	{
		if (v->move_x <= 200)
			v->move_x += incr;
	}
	run_threads_and_draw(v);
}

void	free_resources(t_vars *v)
{
	free(v->tid);
	free(v->t);
	mlx_destroy_image(v->mlx, v->img);
	free(v);
}

void	destroy_window(t_vars *v)
{
	*v->num_windows -= 1;
	mlx_destroy_window(v->mlx, v->win);
	if (*v->num_windows == 0)
	{
		free_resources(v);
		exit(0);
	}
	free_resources(v);
}

int		key_hook(int keycode, t_vars *v)
{
	if (keycode == 53)
		destroy_window(v);
	else if (keycode == 8)
	{
		random_color(v->gradient);
		run_threads_and_draw(v);
	}
	else if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2 || \
		keycode == 126 || keycode == 125 || keycode == 123 || keycode == 124)
		move_xy(keycode, v);
	else if (keycode == 3 && v->max_iterations < 127)
	{
		v->max_iterations++;
		run_threads_and_draw(v);
	}
	else if (keycode == 9 && v->max_iterations > 1)
	{
		v->max_iterations--;
		run_threads_and_draw(v);
	}
	return (0);
}
