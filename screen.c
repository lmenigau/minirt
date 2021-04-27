#include "minirt.h"


void	window(t_global *global)
{
	t_ivec		*reso;
	t_ivec		screen;

	mlx_get_screen_size(global->mlx, &screen.x, &screen.y);
	reso = &global->parse.scene.reso;
	if (reso->x > screen.x)
		reso->x = screen.x;
	if (reso->y > screen.y)
		reso->y = screen.y;
	global->win = mlx_new_window(global->mlx, reso->x, reso->y, "Minirt");
	if (!global->win)
		panic_with_error("window fail\n");
	global->img = mlx_new_image(global->mlx, reso->x, reso->y);
	if (!global->img)
		panic_with_error("image fail\n");
	global->screen = (t_color *)mlx_get_data_addr(global->img, &(int){0}
			, &(int){0}, &(int){0});
	if (!global->screen)
		panic_with_error("image fail\n");
}

void	screen(t_global *global)
{
	t_ivec		*reso;

	reso = &global->parse.scene.reso;
	if (!global->options.save)
	{
		global->mlx = mlx_init();
		if (!global->mlx)
			panic_with_error("connection to the X server failed\n");
		window(global);
		mlx_loop(global->mlx);
	}
	else
	{
		global->screen = malloc(sizeof(t_color) * reso->x * reso->y);
		if (!global->screen)
			panic_with_error("malloc failed\n");
	}
}
