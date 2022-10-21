/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:27 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:28 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

void	parse_tri(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'r');
	if (store->ntris >= 1000)
		panic_with_error(NULL, "Too many triangles");
	store->tris[store->ntris].p1 = parse_vec(parse);
	store->tris[store->ntris].p2 = parse_vec(parse);
	store->tris[store->ntris].p3 = parse_vec(parse);
	store->tris[store->ntris].color = parse_color(parse);
	store->ntris++;
}

void	parse_box(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->nboxs >= 1000)
		panic_with_error(NULL, "Too many boxes");
	store->boxs[store->nboxs].coord = parse_vec(parse);
	store->boxs[store->nboxs].ori = parse_ori(parse);
	store->boxs[store->nboxs].size = parse_num(parse);
	store->boxs[store->nboxs].color = parse_color(parse);
	store->nboxs++;
}

void	parse_plane(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'l');
	if (store->nplanes >= 1000)
		panic_with_error(NULL, "Too many planes");
	store->planes[store->nplanes].coord = parse_vec(parse);
	store->planes[store->nplanes].ori = parse_ori(parse);
	store->planes[store->nplanes].color = parse_color(parse);
	store->nplanes++;
}

void	parse_spherebox(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'q')
		return (parse_box(parse));
	eat(parse, 'p');
	if (store->nspheres >= 1000)
		panic_with_error(NULL, "Too many spheres");
	store->spheres[store->nspheres].coord = parse_vec(parse);
	store->spheres[store->nspheres].size = parse_num(parse) / 2;
	store->spheres[store->nspheres].color = parse_color(parse);
	store->nspheres++;
}
