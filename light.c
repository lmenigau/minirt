#include "minirt.h"
#include <math.h>

t_vec3	col(t_light *light, t_hit hit, t_vec3 lp)
{
	t_vec3	t;
	float	lamb;
	float d;

	d = len(lp);
	lamb = fmaxf(0, dot(norm(lp), hit.n));
	t = hit.c * light->bright * lamb * light->color / (4 * M_PI * d * d);
	return (t);
}

_Bool iter(void *obj, t_ray *ray , int n, _Bool f())
{
	int i = 0;
	while (i < n)
	{
		if (f(&obj[i], ray))
			return (0);
		i++;
	}
	return (1);
}

_Bool visible(t_scene *scene, t_hit hit, t_light *light, t_vec3 *lp)
{
	int i;

	*lp = light->coord - hit.p;
	i = 0;
	while (i < scene->st.nspheres)
	{
		if (hit_sphere(scene->st.spheres[i], (t_ray){hit.p, *lp}, &(t_hit){}))
			return (1);
		i++;
	}
	while (i < scene->st.nplanes)
	{
		if (hit_plane(scene->st.planes[i], (t_ray){hit.p, *lp}, &(t_hit){}))
			return (1);
		i++;
	}
	return (0);
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
		c += visible(scene, hit, &scene->st.lights[i], &lp) * col(&scene->st.lights[i], hit, lp);
		i++;
	}
	return (clamp(c));
}
