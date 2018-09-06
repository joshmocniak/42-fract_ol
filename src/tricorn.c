/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:59:06 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 03:18:08 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_struct_vars_t(t_t_args *t, t_fract_vars *f)
{
	f->w = WIN_WIDTH;
	f->h = WIN_HEIGHT;
	f->c = t->byte_offset;
	f->x = -1;
}

void	init_x_vars_t(t_t_args *t, t_fract_vars *f)
{
	f->new_re = 0;
	f->new_im = 0;
	f->c_re = 1.5 * (t->x + f->x - f->w / 2) / (0.5 * t->v->zoom * f->w) + \
		t->v->move_x;
	f->c_im = (-t->y + f->h / 2) / (0.5 * t->v->zoom * f->h) + t->v->move_y;
	f->i = -1;
}

void	tricorn(t_t_args *t)
{
	t_fract_vars	f;

	init_struct_vars_t(t, &f);
	while (++f.x < t->repeats)
	{
		init_x_vars_t(t, &f);
		while (++f.i < t->v->max_iterations)
		{
			f.old_re = f.new_re;
			f.old_im = f.new_im;
			f.new_re = f.old_re * f.old_re - f.old_im * f.old_im + f.c_re;
			f.new_im = 2 * f.old_re * -f.old_im + f.c_im;
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
