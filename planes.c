/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:38 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:38 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	plane_solver(t_plane pl, t_ray ray)
{
	t_vec3	op;
	float	inter;
	float	denom;

	op = pl.coord - ray.ori;
	denom = dot(ray.dir, pl.ori);
	if (denom < 1e-6 && denom > -1e-6)
		return (-1);
	inter = dot(op, pl.ori) / denom;
	return (inter);
}

void	hit_plane(t_plane pl, t_ray ray, t_hit *hit)
{
	float	d;

	d = plane_solver(pl, ray);
	if (d > 0 && d < hit->d)
	{
		hit->d = d;
		hit->p = ray.ori + ray.dir * d;
		if (dot(ray.dir, pl.ori) < 0)
			hit->n = pl.ori;
		else
			hit->n = mul(pl.ori, -1);
		hit->c = pl.color;
	}
}
