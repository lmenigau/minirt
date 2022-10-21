/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:35 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:35 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"
#include <math.h>

t_vec3	parse_vec(struct s_parse *parse)
{
	t_vec3	vec;

	vec.x = parse_num(parse);
	eat(parse, ',');
	vec.y = parse_num(parse);
	eat(parse, ',');
	vec.z = parse_num(parse);
	return (vec);
}

void	parse_res(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (!parse->scene.isreso)
	{
		parse->scene.reso.x = parse_num(parse);
		parse->scene.reso.y = parse_num(parse);
		parse->scene.isreso = 1;
	}
	else
		panic_with_error(NULL, "multiple resolution");
}

_Bool	in_range(t_vec3 v, float low, float high)
{
	if (v.x < low || v.x > high)
		return (0);
	else if (v.y < low || v.y > high)
		return (0);
	else if (v.z < low || v.z > high)
		return (0);
	return (1);
}

t_vec3	parse_ori(struct s_parse *parse)
{
	t_vec3	c;

	c = parse_vec(parse);
	if (!in_range(c, -1, 1))
		panic_with_error(NULL, "orientation must be between -1 and 1");
	return ((t_vec3){c.x, c.y, c.z});
}

t_vec3	parse_color(struct s_parse *parse)
{
	t_vec3	c;

	c = parse_vec(parse);
	if (!in_range(c, 0, 255))
		panic_with_error(NULL, "color muse be between 0 and 255");
	return ((t_vec3){c.x / 255, c.y / 255, c.z / 255});
}
