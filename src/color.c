/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:58:04 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 01:08:36 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	random_color(int gradient[NUM_COLORS])
{
	int	i;

	i = -1;
	while (++i < NUM_COLORS - 1)
		gradient[i] = rand() % 256 << 16 | rand() % 256 << 8 | rand() % 256;
}

void	default_color(int gradient[NUM_COLORS])
{
	gradient[0] = 6607490;
	gradient[1] = 2037016;
	gradient[2] = 8726055;
	gradient[3] = 13895536;
	gradient[4] = 5268608;
	gradient[5] = 13641546;
	gradient[6] = 8355922;
	gradient[7] = 3514558;
	gradient[8] = 16699563;
	gradient[9] = 0;
}

int		select_color(int c0, int c1, float p)
{
	int result;
	int r[2];
	int	g[2];
	int	b[2];

	result = 0;
	r[0] = (c0 & 0xFF0000) >> 16;
	r[1] = (c1 & 0xFF0000) >> 16;
	g[0] = (c0 & 0x00FF00) >> 8;
	g[1] = (c1 & 0x00FF00) >> 8;
	b[0] = (c0 & 0x0000FF);
	b[1] = (c1 & 0x0000FF);
	result = (int)((r[1] - r[0]) * p + r[0]) << 16 | \
			(int)((g[1] - g[0]) * p + g[0]) << 8 | \
			(int)((b[1] - b[0]) * p + b[0]);
	return (result);
}

int		get_color(int i, int i_max, int gradient[10])
{
	float	p;
	int		c0;
	int		c1;

	p = (float)i / (float)i_max;
	c0 = (int)(p * (10 - 1));
	c1 = (int)ceil(p * (10 - 1));
	p = p * (10 - 1) - c0;
	return (select_color(gradient[c0], gradient[c1], p));
}
