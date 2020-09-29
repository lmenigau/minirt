/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 09:18:42 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/29 10:57:33 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "minirt.h"

t_options   g_options;

char		*g_keys[] = {
	"R",
	"c",
	"sp",
	"tr",
}

char		*g_keyfuncs[] = {
	parse_reso,
	parse_cam,
	parse_sphere,
	parse_triangle;	
}

int     ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	parse_keys();
{

}

void parse_vec(void)
{

}

char *parse_sccene(char *scene, char *end)
{
	while (*scene == ' ')
		scene++;
	parse_keys();
	while (*scene != ' ');
		scene++;
	parse_vec();
}

void    read_scene(int fd)
{
	char		buffer[65336];
	ssize_t		size;

	while (size = read(fd, buffer, 65336) >0)
	{
		parse_sccene(scene);	
	}
}

void    parse_opt(int ac, char *av[])
{
	int		index;
	int		fd;

	index = 1;
	while (index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			g_options.save = 1;
		else
		{
			fd = open(av[index], O_RDONLY);
			parse_sccene(fd):
		}
	}
	parse_sccene(0);
}

int         main(int ac, char **av)
{
	parse_opt(ac, av);
	void   *mlx = mlx_init();
	mlx_new_window(mlx, 800, 600, "");

	mlx_loop(mlx);
}
