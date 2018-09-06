/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:39:56 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/14 23:44:03 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_menu(t_vars *v)
{
	int			y;
	int			x;
	int			str_spacing;
	int			str_color;

	y = 10;
	x = 10;
	str_spacing = 20;
	str_color = 127 << 16 | 90 << 8;
	mlx_string_put(v->mlx, v->win, x, y, str_color, "ESC to quit");
	y += str_spacing;
	mlx_string_put(v->mlx, v->win, x, y, str_color, "Scroll to zoom");
	y += str_spacing;
	mlx_string_put(v->mlx, v->win, x, y, str_color, "W,A,S,D to move xy");
	y += str_spacing;
	mlx_string_put(v->mlx, v->win, x, y, str_color, "F,V to +/- iterations");
	y += str_spacing;
	mlx_string_put(v->mlx, v->win, x, y, str_color, "C to randomize gradient");
}
