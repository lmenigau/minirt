/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 09:18:42 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/27 14:56:19 by lomeniga         ###   ########.fr       */
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

void	parse_opt(t_global *global, int ac, char *av[])
{
	int					index;
	int					fd;

	index = 1;
	while (index < 3 && index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			global->options.save = 1;
		else
		{
			fd = open(av[index], O_RDONLY);
			if (fd < 0)
				panic_with_error("");
			parse_scene(global, fd);
		}
		index++;
	}
}

int	main(int ac, char **av)
{
	t_global	*global;

	global = init_global();
	screen(global);
	parse_opt(global, ac, av);
	mlx_loop(global->mlx);
}
