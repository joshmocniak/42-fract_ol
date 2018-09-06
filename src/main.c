/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 02:20:10 by jmocniak          #+#    #+#             */
/*   Updated: 2018/07/15 03:06:03 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_putendl("Usage: ./fractol <fractol type> ...\n");
	ft_putendl("Types:\n\tjulia\n\tmandelbrot\n\tburningship\n\ttricorn");
	exit(0);
}

int		validate_args(int argc, char **argv)
{
	unsigned int	fractals;
	int				i;

	i = 0;
	fractals = 0;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "julia"))
			fractals |= JULIA;
		else if (!ft_strcmp(argv[i], "mandelbrot"))
			fractals |= MANDELBROT;
		else if (!ft_strcmp(argv[i], "burningship"))
			fractals |= BURNINGSHIP;
		else if (!ft_strcmp(argv[i], "tricorn"))
			fractals |= TRICORN;
		else
		{
			ft_putendl("error: invalid fractal.\n");
			print_usage();
		}
		i++;
	}
	return (fractals);
}

int		main(int argc, char **argv)
{
	int		fractals;
	void	*mlx;
	int		num_windows;

	if (argc >= 2)
	{
		srand(time(0));
		fractals = validate_args(argc - 1, argv + 1);
		mlx = mlx_init();
		num_windows = 0;
		if (fractals & JULIA)
			window_julia(mlx, &num_windows);
		if (fractals & MANDELBROT)
			window_mandelbrot(mlx, &num_windows);
		if (fractals & BURNINGSHIP)
			window_burningship(mlx, &num_windows);
		if (fractals & TRICORN)
			window_tricorn(mlx, &num_windows);
		mlx_loop(mlx);
	}
	else
		print_usage();
	return (0);
}
