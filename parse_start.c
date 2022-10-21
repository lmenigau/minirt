/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:32 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:32 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

void	parse_bigl(struct s_parse *parse)
{
	if (parse->scene.islight)
		panic_with_error(NULL, "there must be a signle L light");
	else
		parse_light(parse);
	parse->scene.islight = 1;
}

void	parse_camcyl(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->ncams >= 1000)
		panic_with_error(NULL, "Too many cameras");
	parse_cam(parse);
}

void	parse_object(struct s_parse *parse)
{
	if (parse->current == 'R')
		parse_res(parse);
	else if (parse->current == 'A')
		parse_ambiant(parse);
	else if (parse->current == 'C')
		parse_bigc(parse);
	else if (parse->current == 'c')
		parse_camcyl(parse);
	else if (parse->current == 'L')
		parse_bigl(parse);
	else if (parse->current == 'l')
		parse_light(parse);
	else if (parse->current == 's')
		parse_spherebox(parse);
	else if (parse->current == 'p')
		parse_plane(parse);
	else if (parse->current == 't')
		parse_tri(parse);
	else if (parse->current == '\n')
		;
	else
		panic_with_error(NULL, "undefined object");
}

void	parse_line(struct s_parse *parse)
{
	next_token(parse);
	parse_object(parse);
	next_token(parse);
	eat(parse, '\n');
}

void	parse_scene(t_global *global, int fd)
{
	init_scene(&global->parse.scene);
	global->parse.buf.fd = fd;
	parse_line(&global->parse);
	while (global->parse.buf.len > 0)
	{
		parse_line(&global->parse);
	}
	if (!global->parse.scene.islight)
		panic_with_error(NULL, "big L light is missing");
	if (!global->parse.scene.iscam)
		panic_with_error(NULL, "big C camera is missing");
	if (!global->parse.scene.isambiant)
		panic_with_error(NULL, "Ambiant light is missing");
}
