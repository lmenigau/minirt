#include "minirt.h"

void	screen(t_global *global)
{
	if (global->options.save)
	{
		global->mlx = mlx_init();
		if (!global->mlx)
			panic_with_error("connection to the X server failed\n");
		mlx_new_window(global->mlx, global->parse.scene.reso.x,
			global->parse.scene.reso.y, "");
		global->screen = mlx_new_image(global->mlx, global->parse.scene.reso.x,
				global->parse.scene.reso.y);
	}
	else
	{
		global->screen = malloc(sizeof(t_color) * global->parse.scene.reso.x
				* global->parse.scene.reso.y);
	}
}
