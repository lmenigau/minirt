/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 09:18:42 by lomeniga          #+#    #+#             */
/*   Updated: 2021/01/21 16:32:07 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include "minirt.h"

t_options	g_options;
char		*g_keys[] = {
	"R",
	"c",
	"sp",
	"tr",
};
/*
* char		*g_keyfuncs[] = {
*  parse_reso,
*  parse_cam,
*  parse_sphere,
*  parse_triangle;
* }
*/

static int      ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int             ft_atoi(char **fmt)
{
	int		nb;
	char	*str;

	str = *fmt;
	nb = 0;
	while (*str && ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	*fmt = str - 1;
	return (nb);
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

void   parse_keys(char *scene, size_t index)
{

}

int parse_vec(void)
{

	return (0);
}

int  parse_res()
{

	return (0);
}

int parse_tr()
{
	return (0);
}

int	parse_object()
{
	return (0);
}

int  parse_line()
{
	return (0);
}

int parse_scene(int fd)
{
	struct	s_parse;

	return (0);
}
void	panic_with_error()
{
	perror(NULL);
	exit(1);
}

void    read_scene(struct s_buf *buf)
{
	ssize_t		size;

	size = read(buf->fd, buf, 4096);
	if (size < 0) 
		panic_with_error();
	buf->len = size;
	buf->index = 0;
}

void    parse_opt(int ac, char *av[])
{
	int		index;
	int		fd;

	index = 1;
	while (index < 3 && index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			g_options.save = 1;
		else
		{
			fd = open(av[index], O_RDONLY);
			parse_scene(fd);
		}
	}
}

int         main(int ac, char **av)
{
	parse_opt(ac, av);
	void   *mlx = mlx_init();
	if (!mlx)
		return (0);
	mlx_new_window(mlx, 800, 600, "");

	mlx_loop(mlx);
}
