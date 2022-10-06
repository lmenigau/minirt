#include "minirt.h"

t_vec3	col(t_light *light, t_hit hit)
{
	t_vec3	lp;
	t_vec3	t;
	float	lamb;
	float d;

	lp = light->coord - hit.p;
	d = len(lp);
	lamb = fmaxf(0, dot(norm(lp), hit.n));
	t = hit.c * light->bright * lamb * light->color / (4 * M_PI * d * d);
	return (t);
}

t_vec3	light(t_scene *scene, t_hit hit)
{
	int		i;
	t_vec3	c;

	c = scene->ambiant * hit.c * .5;
	i = 0;
	while (i < scene->st.nlights)
	{
		c += col(&scene->st.lights[i], hit) * 100;
		i++;
	}
	return (c);
}
