/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 09:18:42 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/09 16:07:08 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	panic_with_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	parse_opt(int ac, char *av[])
{
	struct s_options	options;
	int					index;
	int					fd;

	index = 1;
	while (index < 3 && index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			options.save = 1;
		else
		{
			fd = open(av[index], O_RDONLY);
			parse_scene(fd);
		}
	}
}

int	main(int ac, char **av)
{
	parse_opt(ac, av);
	void *(mlx) = mlx_init();
	if (!mlx)
		return (0);
	mlx_new_window(mlx, 800, 600, "");
	mlx_loop(mlx);
}
