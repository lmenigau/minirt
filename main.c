/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:12 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:13 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stddef.h>

void	print(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

void	panic_with_error(t_global *g, char *msg)
{
	print("Error\n");
	if (errno)
		perror(msg);
	else
		printf("%s\n", msg);
	if (g)
	{
		if (g->img)
			mlx_destroy_image(g->mlx, g->img);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		if (g->mlx)
			mlx_destroy_display(g->mlx);
		if (g->mlx)
			free(g->mlx);
	}
	exit(1);
}

void	parse_opt(t_global *global, int ac, char *av[])
{
	int					index;
	int					fd;

	index = 1;
	fd = -2;
	while (index < 3 && index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			global->options.save = 1;
		else if (fd == -2)
		{
			fd = open(av[index], O_RDONLY);
			if (fd < 0)
				panic_with_error(global, av[index]);
			if (ft_strcmp(av[index] + (ft_strlen(av[index]) - 3), ".rt"))
				panic_with_error(global, "missing .rt extension");
			parse_scene(global, fd);
		}
		else
			panic_with_error(NULL, "Too many arguments");
		index++;
	}
	if (fd == -2)
		panic_with_error(global, "input file missing\n");
}

int	main(int ac, char **av)
{
	t_global	*global;

	global = init_global();
	parse_opt(global, ac, av);
	screen(global);
	if (!global->options.save)
	{
		mlx_destroy_image(global->mlx, global->img);
		mlx_destroy_window(global->mlx, global->win);
		mlx_destroy_display(global->mlx);
		free(global->mlx);
	}
}
