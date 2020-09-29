#include <unistd.h>
#include "mlx.h"


void 	parse_scene(int fd)
{
	char buffer[65336];
	ssize_t		size;

	size = read(fd, buffer, 65336);
}

void	parse_opt(int ac, char *av[])
{
}

int			main(int ac, char **av)
{
	void *mlx = mlx_init();

	mlx_new_window(mlx, 800, 600, ""); 

	mlx_loop(mlx);
}
