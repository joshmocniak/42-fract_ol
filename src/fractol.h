/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 07:30:11 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/06 14:42:56 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../42-libft/libft.h"
# include "../libmlx/mlx.h"
# include <math.h>
# include <time.h>
# include <pthread.h>

# define JULIA 1
# define MANDELBROT 2
# define BURNINGSHIP 4
# define TRICORN 8
# define WIN_HEIGHT 600
# define WIN_WIDTH 600
# define NUM_COLORS 10
# define THREADS (WIN_HEIGHT / 12)
# define MAX_ITERATIONS 30

typedef struct s_t_args	t_t_args;

typedef struct	s_vars
{
	int			*num_windows;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			bytes_per_pixel;
	int			max_iterations;
	double		c_re;
	double		c_im;
	double		zoom;
	int			zoom_incr;
	double		move_x;
	double		move_y;
	int			gradient[NUM_COLORS];
	pthread_t	*tid;
	t_t_args	*t;
	int			num_threads;
	void		(*funct)(t_t_args *t);
}				t_vars;

struct			s_t_args
{
	t_vars		*v;
	int			y;
	int			x;
	int			byte_offset;
	int			row_byte_offset;
	int			repeats;
};

typedef struct	s_fract_vars
{
	int			w;
	int			h;
	unsigned	color;
	int			c;
	int			x;
	int			i;
	double		new_re;
	double		new_im;
	double		old_re;
	double		old_im;
	double		c_re;
	double		c_im;
}				t_fract_vars;

typedef struct	s_process_thread
{
	int			rtp;
	int			rofr;
	int			rolr;
	int			ri;
	int			orig_x;
	int			orig_y;
	int			orig_repeats;
}				t_process_thread;

void			window_julia(void *mlx, int *num_windows);
void			window_mandelbrot(void *mlx, int *num_windows);
void			window_burningship(void *mlx, int *num_windows);
void			window_tricorn(void *mlx, int *num_windows);
void			julia(t_t_args *t);
void			mandelbrot(t_t_args *t);
void			burningship(t_t_args *t);
void			tricorn(t_t_args *t);
int				key_hook(int key, t_vars *v);
int				mouse_hook(int button, int x, int y, t_vars *v);
int				mouse_xy_hook_julia(int x, int y, t_vars *v);
int				get_color(int i, int i_max, int gradient[NUM_COLORS]);
void			random_color(int gradient[NUM_COLORS]);
void			default_color(int gradient[NUM_COLORS]);
void			error(char *str);
void			prep_threads(t_vars *v, int num_threads);
void			print_menu(t_vars *v);
void			run_threads_and_draw(t_vars *v);

#endif
