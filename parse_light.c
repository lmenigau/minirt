/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:21 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:22 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

void	parse_ambiant(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (!parse->scene.isambiant)
	{
		parse->scene.ambiant_r = parse_num(parse);
		if (parse->scene.ambiant_r < 0 || parse->scene.ambiant_r > 1)
			panic_with_error(NULL, "Ambiant ratio must be in the range 0 to 1");
		parse->scene.ambiant = mul(parse_color(parse), parse->scene.ambiant_r);
		parse->scene.isambiant = 1;
	}
	else
		panic_with_error(NULL, "multiple ambiant");
}

void	parse_light(struct s_parse *parse)
{
	t_store	*store;
	float	b;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->nlights >= 1000)
		panic_with_error(NULL, "Too many lights");
	store->lights[store->nlights].coord = parse_vec(parse);
	b = parse_num(parse);
	if (b < 0 || b > 1)
		panic_with_error(NULL, "Brightness must be in the range 0 to 1");
	store->lights[store->nlights].bright = b;
	store->lights[store->nlights].color = parse_color(parse);
	store->nlights++;
}
