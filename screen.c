#include "minirt.h"

void	store_pixel(t_global *global, t_ivec pos, t_color col)
{
	unsigned int	*ptr;

	ptr = (unsigned int *)(global->screen + pos.y
			* global->sizeline + pos.x * sizeof (unsigned int));
	*ptr = mlx_get_color_value(global->mlx, col.r << 16 | col.g << 8 | col.b);
}

void	iterate_pixels(t_global *global)
{
	t_ivec	it;
	t_color	col;
	t_ivec	reso;

	it.y = 0;
	reso = global->parse.scene.reso;
	while (it.y < reso.y)
	{
		it.x = 0;
		while (it.x < reso.x)
		{
			col = render(global, it);
			store_pixel(global, it, col);
			it.x++;
		}
		it.y++;
	}
}

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
	global->screen = mlx_get_data_addr(global->img, &(int){0},
			&global->sizeline, &(int){0});
	global->ratio = reso->x / (float)reso->y;
}

void	screen(t_global *global)
{
	t_ivec		*reso;

	reso = &global->parse.scene.reso;
    *reso = (t_ivec){1920, 1080};
	if (!global->options.save)
	{
		global->mlx = mlx_init();
		if (!global->mlx)
			panic_with_error("connection to the X server failed\n");
		window(global);
		iterate_pixels(global);
		mlx_put_image_to_window(global->mlx, global->win, global->img, 0, 0);
		mlx_loop(global->mlx);
	}
	else
	{
		global->screen = malloc(sizeof(t_color) * reso->x * reso->y);
		if (!global->screen)
			panic_with_error("malloc failed\n");
	}
}
