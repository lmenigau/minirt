/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_inter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:24 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:24 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_inter(t_vec2 *inter, t_ray ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;

	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * (ray.ori.x * ray.dir.x + ray.ori.y * ray.dir.y);
	c = ray.ori.x * ray.ori.x + ray.ori.y * ray.ori.y - 1;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		(*inter).x = (-b + sqrtf(delta)) / (2 * a);
		(*inter).y = (-b - sqrtf(delta)) / (2 * a);
		return (0);
	}
	return (1);
}

float	cyl_solver(t_ray ray)
{
	t_vec2	inter;
	float	z;

	if (set_inter(&inter, ray) == 1)
		return (-1);
	if (inter.x > 0 && (inter.y < 0 || inter.x < inter.y))
	{
		z = ray.ori.z + inter.x * ray.dir.z;
		if (z >= -1 && z <= 1)
			return (inter.x);
	}
	else if (inter.y > 0 && (inter.x < 0 || inter.y < inter.x))
	{
		z = ray.ori.z + inter.y * ray.dir.z;
		if (z >= -1 && z <= 1)
			return (inter.y);
	}
	return (-1);
}

float	caps_solver(t_ray ray)
{
	t_vec2	inter;
	float	x;
	float	y;
	t_plane	pl;

	pl.coord = (t_vec3){0, 0, 1};
	pl.ori = (t_vec3){0, 0, 1};
	inter.x = plane_solver(pl, ray);
	pl.coord.z = -1;
	inter.y = plane_solver(pl, ray);
	if (inter.x > 0 && (inter.y < 0 || inter.x < inter.y))
	{
		x = ray.ori.x + inter.x * ray.dir.x;
		y = ray.ori.y + inter.x * ray.dir.y;
		if (x * x + y * y <= 1)
			return (inter.x);
	}
	else if (inter.y > 0 && (inter.x < 0 || inter.y < inter.x))
	{
		x = ray.ori.x + inter.y * ray.dir.x;
		y = ray.ori.y + inter.y * ray.dir.y;
		if (x * x + y * y <= 1)
			return (inter.y);
	}
	return (-1);
}

_Bool	cyl_inter(t_vec2 d, t_cyl cy, t_ray ray, t_hit *hit)
{
	float	world_d;
	t_vec3	v;
	t_vec3	p;
	t_ray	loc_ray;

	if (d.x > 0 && (d.y < 0 || d.x <= d.y))
	{
		loc_ray = set_locray(cy, ray);
		v = loc_ray.ori + loc_ray.dir * d.x;
		p = set_worldpoint(cy, v);
		world_d = (p.x - ray.ori.x) / ray.dir.x;
		if (world_d < 1 || world_d >= hit->d)
			return (0);
		hit->p = p;
		hit->d = world_d;
		hit->n = norm(set_worldpoint(cy, (t_vec3){v.x, v.y, 0})
				- set_worldpoint(cy, (t_vec3){0, 0, 0}));
		hit->c = cy.color;
		return (1);
	}
	return (0);
}

_Bool	caps_inter(t_vec2 d, t_cyl cy, t_ray ray, t_hit *hit)
{
	float	world_d;
	t_vec3	v;
	t_vec3	p;
	t_ray	loc_ray;

	if (d.y > 0 && (d.x < 0 || d.y < d.x))
	{
		loc_ray = set_locray(cy, ray);
		v = add(loc_ray.ori, mul(loc_ray.dir, d.y));
		p = set_worldpoint(cy, v);
		world_d = (p.x - ray.ori.x) / ray.dir.x;
		if (world_d < 1 || world_d >= hit->d)
			return (0);
		hit->p = p;
		hit->d = world_d;
		hit->n = norm(set_worldpoint(cy, (t_vec3){0, 0, v.z})
				- set_worldpoint(cy, (t_vec3){0, 0, 0}));
		hit->c = cy.color;
		return (1);
	}
	return (0);
}
