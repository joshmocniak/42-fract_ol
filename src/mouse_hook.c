/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:44:01 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 01:05:02 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, t_vars *v)
{
	(void)x;
	(void)y;
	if (button == 5 && v->zoom < ~0ULL - v->zoom_incr)
	{
		v->zoom += v->zoom_incr;
		v->zoom_incr *= 4;
	}
	else if (button == 4 && v->zoom > 1)
	{
		v->zoom_incr /= 4;
		v->zoom -= v->zoom_incr;
	}
	run_threads_and_draw(v);
	return (0);
}

int		mouse_xy_hook_julia(int x, int y, t_vars *v)
{
	v->c_re = (x / (WIN_WIDTH / 2.0)) - 1.0;
	v->c_im = (y / (WIN_HEIGHT / 2.0)) - 1.0;
	run_threads_and_draw(v);
	return (0);
}
