#include "minirt.h"

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
	print(msg);
	if (errno)
		perror(msg);
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
	fd = -2;
	while (index < 3 && index < ac)
	{
		if (av[index][0] == '-' && !ft_strcmp(av[index], "--save"))
			global->options.save = 1;
		else
		{
			fd = open(av[index], O_RDONLY);
			if (fd < 0)
				panic_with_error(global, av[index]);
			parse_scene(global, fd);
		}
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
