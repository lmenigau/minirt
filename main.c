/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 09:18:42 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/16 15:18:47 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <execinfo.h>

void	print(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

void	panic_with_error(char *msg)
{
	void	*array[10];
	backtrace(array, 10);
	backtrace_symbols_fd(array, 10, 1);
	print("Error\n");
	print(msg);
	if (errno)
		perror(msg);
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
			if (fd < 0)
				panic_with_error("");
			parse_scene(fd);
		}
		index++;
	}
}

int	main(int ac, char **av)
{
	parse_opt(ac, av);
	void *(mlx) = mlx_init();
	if (!mlx)
		panic_with_error("connection to the X server failed\n");
	mlx_new_window(mlx, 800, 600, "");
	mlx_loop(mlx);
}
