#include "minirt.h"
#include <math.h>

t_vec3	col(t_light *light, t_hit hit, t_vec3 lp)
{
	t_vec3	t;
	float	lamb;
	float d;

	d = len(lp);
	lamb = fmaxf(0, dot(norm(lp), hit.n));
	t = hit.c * light->bright * 1024 * lamb * light->color / (M_PI * d * d);
	return (t);
}

_Bool visible(t_scene *scene, t_hit hit, t_light *light, t_vec3 *lp)
{
	int i;
	float d;

	*lp = (light->coord - hit.p);
	t_vec3 pl = norm(*lp);
	i = 0;
	while (i < scene->st.nplanes)
	{
		d = plane_solver(scene->st.planes[i], (t_ray){pl, hit.p + pl * 0x1p-10f});
		if (d > 0 && d < len(*lp))
			return (0);
		i++;
	}
	i = 0;
	while (i < scene->st.nspheres)
	{
		d = sphere_solver(scene->st.spheres[i], (t_ray){pl, hit.p + pl * 0x1p-10f});
		if (d > 0 && d < len(*lp))
			return (0);
		i++;
	}
	return (1);
}

t_vec3	light(t_scene *scene, t_hit hit)
{
	int		i;
	t_vec3	c;
	t_vec3	lp;

	c = scene->ambiant * hit.c;
	i = 0;
	while (i < scene->st.nlights)
	{
		if (visible(scene, hit, &scene->st.lights[i], &lp))
			c += col(&scene->st.lights[i], hit, lp);
		i++;
	}
	return (clamp(c));
}
