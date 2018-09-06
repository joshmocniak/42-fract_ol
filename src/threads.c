/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 01:10:40 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 01:43:11 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	process_thread_helper(t_t_args *j, t_process_thread *p)
{
	p->orig_x = j->x;
	p->orig_y = j->y;
	p->orig_repeats = j->repeats;
	p->rtp = ((j->x + j->repeats) / WIN_WIDTH) + \
		(((j->x + j->repeats) % WIN_WIDTH) > 0);
	p->rofr = WIN_WIDTH - j->x;
	p->rolr = ((j->x + j->repeats) % WIN_WIDTH);
	if (p->rolr == 0)
		p->rolr = WIN_WIDTH;
	j->repeats = p->rofr;
	j->byte_offset = j->row_byte_offset + j->x * j->v->bytes_per_pixel;
	j->v->funct(j);
	p->ri = 0;
	j->byte_offset = j->row_byte_offset + j->v->size_line;
	j->repeats = WIN_WIDTH;
	j->x = 0;
	j->y++;
}

void	*process_thread(void *k)
{
	t_t_args			*j;
	t_process_thread	p;

	j = (t_t_args *)k;
	if (j->x + j->repeats > WIN_WIDTH)
	{
		process_thread_helper(j, &p);
		while (++(p.ri) < p.rtp - 1)
		{
			j->v->funct(j);
			j->byte_offset = j->byte_offset + j->v->size_line;
			j->y++;
		}
		j->repeats = p.rolr;
		j->v->funct(j);
		j->x = p.orig_x;
		j->y = p.orig_y;
		j->repeats = p.orig_repeats;
		return (NULL);
	}
	j->byte_offset = j->row_byte_offset + j->x * j->v->bytes_per_pixel;
	j->v->funct(j);
	return (NULL);
}

void	run_threads_and_draw(t_vars *v)
{
	int			y;

	y = -1;
	while (++y < v->num_threads)
		pthread_create(&v->tid[y], NULL, process_thread, &v->t[y]);
	y = -1;
	while (++y < v->num_threads)
		pthread_join(v->tid[y], NULL);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	print_menu(v);
}

void	store_thread_data(t_vars *v, int *ti, int ppt, int threads)
{
	while (*ti < threads - 1)
	{
		v->t[*ti].x = (*ti * ppt) % WIN_WIDTH;
		v->t[*ti].y = *ti * ppt / WIN_WIDTH;
		v->t[*ti].repeats = ppt;
		v->t[*ti].row_byte_offset = *ti * ppt / WIN_WIDTH * v->size_line;
		v->t[*ti].v = v;
		(*ti)++;
	}
}

void	prep_threads(t_vars *v, int num_threads)
{
	int			threads;
	int			ti;
	int			ppt;
	int			pilt;

	if (num_threads < 1)
		threads = 1;
	else
		threads = num_threads;
	v->num_threads = threads;
	v->tid = (pthread_t *)malloc(sizeof(pthread_t) * threads);
	v->t = (t_t_args *)malloc(sizeof(t_t_args) * threads);
	if (v->t == NULL || v->tid == NULL)
		error("error: failed to allocate threads");
	ppt = WIN_HEIGHT * WIN_WIDTH / threads;
	pilt = (WIN_HEIGHT * WIN_WIDTH) % threads;
	ti = 0;
	store_thread_data(v, &ti, ppt, threads);
	v->t[ti].x = (ti * ppt) % WIN_WIDTH;
	v->t[ti].y = ti * ppt / WIN_WIDTH;
	v->t[ti].repeats = ppt + pilt;
	v->t[ti].row_byte_offset = ti * ppt / WIN_WIDTH * v->size_line;
	v->t[ti].v = v;
}
