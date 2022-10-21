/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:08 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:55:53 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec3	col(t_light *light, t_hit hit, t_vec3 lp)
{
	t_vec3	t;
	float	lamb;
	float	d;

	d = len(lp);
	lamb = fmaxf(0, dot(norm(lp), hit.n));
	t = hit.c * light->bright * 800 * lamb * light->color / (M_PI * d * d);
	return (t);
}

_Bool	visible_cyl(t_scene *scene, float max_d, t_ray ray)
{
	int		i;
	float	d;
	t_hit	h;

	i = 0;
	while (i < scene->st.ncyls)
	{
		h.d = INFINITY;
		hit_cyl(scene->st.cyls[i], ray, &h);
		d = h.d;
		if (d > 0 && d < max_d)
			return (0);
		i++;
	}
	return (1);
}

_Bool	visible(t_scene *scene, float max_d, t_ray ray)
{
	int		i;
	float	d;

	i = 0;
	while (i < scene->st.nplanes)
	{
		d = plane_solver(scene->st.planes[i], ray);
		if (d > 0 && d < max_d)
			return (0);
		i++;
	}
	i = 0;
	while (i < scene->st.nspheres)
	{
		d = sphere_solver(scene->st.spheres[i], ray);
		if (d > 0 && d < max_d)
			return (0);
		i++;
	}
	return (visible_cyl(scene, max_d, ray));
}

t_vec3	light(t_scene *scene, t_hit hit)
{
	int		i;
	t_vec3	c;
	t_vec3	lp;
	t_vec3	pl;

	c = scene->ambiant * hit.c;
	i = 0;
	while (i < scene->st.nlights)
	{
		lp = (scene->st.lights[i].coord - hit.p);
		pl = norm(lp);
		if (visible(scene, len(lp), (t_ray){pl, hit.p + pl * .0009765625}))
			c += col(&scene->st.lights[i], hit, lp);
		i++;
	}
	return (clamp(c));
}
