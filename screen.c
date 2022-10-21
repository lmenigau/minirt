/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:50 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:51 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	store_pixel(t_global *global, t_ivec pos, t_color col)
{
	unsigned int	*ptr;

	ptr = (unsigned int *)(global->screen + pos.y
			* global->sizeline + pos.x * sizeof (unsigned int));
	*ptr = mlx_get_color_value(global->mlx, col.r << 16 | col.g << 8 | col.b);
}

int	escape(int keysim, t_global *global)
{
	if (keysim == XK_ESCAPE)
		mlx_loop_end(global->mlx);
	return (0);
}

int	win_close(t_global *global)
{
	mlx_loop_end(global->mlx);
	return (0);
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
		panic_with_error(global, "window fail\n");
	global->img = mlx_new_image(global->mlx, reso->x, reso->y);
	if (!global->img)
		panic_with_error(global, "image fail\n");
	global->screen = mlx_get_data_addr(global->img, &(int){0},
			&global->sizeline, &(int){0});
	global->ratio = reso->y / (float)reso->x;
	mlx_key_hook(global->win, escape, global);
	mlx_hook(global->win, DESTROYNOTIFY, 0, win_close, global);
}

void	screen(t_global *global)
{
	t_ivec		*reso;

	reso = &global->parse.scene.reso;
	if (!global->options.save)
	{
		global->mlx = mlx_init();
		if (!global->mlx)
			panic_with_error(global, "connection to the X server failed\n");
		window(global);
		iterate_pixels(global);
		mlx_put_image_to_window(global->mlx, global->win, global->img, 0, 0);
		mlx_loop(global->mlx);
	}
	else
	{
		global->screen = malloc(sizeof(t_color) * reso->x * reso->y);
		if (!global->screen)
			panic_with_error(NULL, "malloc failed\n");
		free(global->screen);
	}
}
