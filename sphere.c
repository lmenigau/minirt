/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:56 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:57 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

float	sphere_solver(t_sphere sp, t_ray ray)
{
	float	delta;
	t_vec3	oc;
	t_vec2	inter;
	t_vec3	v;

	oc = ray.ori - sp.coord;
	v = (t_vec3){dot(ray.dir, ray.dir), 2 * dot(ray.dir, oc),
		dot(oc, oc) - sp.size * sp.size};
	delta = v.y * v.y - 4 * v.x * v.z;
	if (delta >= 0)
	{
		inter.x = (-v.y + sqrtf(delta)) / (2 * v.x);
		inter.y = (-v.y - sqrtf(delta)) / (2 * v.x);
		if (inter.x < 0)
			return (inter.y);
		else if (inter.y < 0)
			return (inter.x);
		else if (inter.x < inter.y)
			return (inter.x);
		else
			return (inter.y);
	}
	return (-1);
}

void	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit)
{
	float	d;

	d = sphere_solver(sp, ray);
	if (d > 1 && d < hit->d)
	{
		hit->d = d;
		hit->p = ray.ori + ray.dir * d;
		hit->n = norm(hit->p - sp.coord);
		hit->c = sp.color;
	}
}
