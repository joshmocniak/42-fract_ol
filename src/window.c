/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:50:29 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 03:25:16 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	populate_generic_t_vars(t_vars *v, char *window_title)
{
	*v->num_windows += 1;
	v->win = mlx_new_window(v->mlx, WIN_WIDTH, WIN_HEIGHT, window_title);
	v->img = mlx_new_image(v->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (v->img == NULL)
		error("error:  failed to create new image");
	v->data_addr = mlx_get_data_addr(v->img, &v->bits_per_pixel, \
			&v->size_line, &v->endian);
	v->bytes_per_pixel = v->bits_per_pixel / 8;
	v->max_iterations = MAX_ITERATIONS;
	default_color(v->gradient);
	v->move_x = 0;
	v->move_y = 0;
	v->zoom = .5;
	v->zoom_incr = 2;
}

void	window_julia(void *mlx, int *num_windows)
{
	t_vars	*v;

	v = (t_vars *)malloc(sizeof(t_vars));
	v->mlx = mlx;
	v->num_windows = num_windows;
	populate_generic_t_vars(v, "Julia");
	v->c_re = -0.7;
	v->c_im = 0.27015;
	v->funct = julia;
	prep_threads(v, THREADS);
	run_threads_and_draw(v);
	mlx_hook(v->win, 6, 0, mouse_xy_hook_julia, v);
	mlx_key_hook(v->win, key_hook, v);
	mlx_mouse_hook(v->win, mouse_hook, v);
}

void	window_mandelbrot(void *mlx, int *num_windows)
{
	t_vars	*v;

	v = (t_vars *)malloc(sizeof(t_vars));
	v->mlx = mlx;
	v->num_windows = num_windows;
	populate_generic_t_vars(v, "Mandelbrot");
	v->funct = mandelbrot;
	prep_threads(v, THREADS);
	run_threads_and_draw(v);
	mlx_key_hook(v->win, key_hook, v);
	mlx_mouse_hook(v->win, mouse_hook, v);
}

void	window_burningship(void *mlx, int *num_windows)
{
	t_vars	*v;

	v = (t_vars *)malloc(sizeof(t_vars));
	v->mlx = mlx;
	v->num_windows = num_windows;
	populate_generic_t_vars(v, "Burning Ship");
	v->funct = burningship;
	prep_threads(v, THREADS);
	run_threads_and_draw(v);
	mlx_key_hook(v->win, key_hook, v);
	mlx_mouse_hook(v->win, mouse_hook, v);
}

void	window_tricorn(void *mlx, int *num_windows)
{
	t_vars	*v;

	v = (t_vars *)malloc(sizeof(t_vars));
	v->mlx = mlx;
	v->num_windows = num_windows;
	populate_generic_t_vars(v, "Tricorn");
	v->funct = tricorn;
	prep_threads(v, THREADS);
	run_threads_and_draw(v);
	mlx_key_hook(v->win, key_hook, v);
	mlx_mouse_hook(v->win, mouse_hook, v);
}
