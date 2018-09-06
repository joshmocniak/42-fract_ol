/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:04:29 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 02:36:11 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_struct_vars_j(t_t_args *t, t_fract_vars *f)
{
	f->w = WIN_WIDTH;
	f->h = WIN_HEIGHT;
	f->c = t->byte_offset;
	f->x = -1;
}

void	julia(t_t_args *t)
{
	t_fract_vars	f;

	init_struct_vars_j(t, &f);
	while (++f.x < t->repeats)
	{
		f.new_re = 1.5 * ((t->x + f.x) - f.w / 2) \
			/ (0.5 * t->v->zoom * f.w) + t->v->move_x;
		f.new_im = (-t->y + f.h / 2) / (0.5 * t->v->zoom * f.h) + t->v->move_y;
		f.i = -1;
		while (++f.i < t->v->max_iterations)
		{
			f.old_re = f.new_re;
			f.old_im = f.new_im;
			f.new_re = f.old_re * f.old_re - f.old_im * f.old_im + t->v->c_re;
			f.new_im = 2 * f.old_re * f.old_im + t->v->c_im;
			if ((f.new_re * f.new_re + f.new_im * f.new_im) > 4)
				break ;
		}
		f.color = mlx_get_color_value(t->v->mlx, \
				get_color(f.i, t->v->max_iterations, t->v->gradient));
		t->v->data_addr[f.c++] = (f.color & 0xFF0000) >> 16;
		t->v->data_addr[f.c++] = (f.color & 0x00FF00) >> 8;
		t->v->data_addr[f.c++] = (f.color & 0x0000FF);
		t->v->data_addr[f.c++] = 0;
	}
}
