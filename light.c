#include "minirt.h"

t_vec3	col(t_light *light, t_hit hit)
{
	t_vec3	lp;
	t_vec3	t;
	float	lamb;

	lp = sub(light->coord, hit.p);
	lamb = dot(hit.n, norm(lp));
	t = mul(hit.c, fmaxf(0, lamb));
	t = vmul(t, light->color);
	//t = mul(t, light->bright / (len(lp) * len(lp)));
	return (t);
}

t_vec3	light(t_scene *scene, t_hit hit)
{
	int		i;
	t_vec3	c;

	c = vmul(scene->ambiant, hit.c);
	i = 0;
	while (i < scene->st.nlights)
	{
		c = add(c, col(&scene->st.lights[i], hit));
		i++;
	}
	return (c);
}
