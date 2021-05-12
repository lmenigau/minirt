#include "minirt.h"

t_vec3	col(t_scene *scene, t_hit hit, int i)
{
	t_vec3 t;

	t = norm(sub(scene->st.lights[i].coord, hit.p));
	t = mul(scene->st.lights[i].color, dot(hit.n, t));
	t = vmul(hit.c, t);

	return (t);
}

t_vec3 light(t_scene *scene, t_hit hit)
{
	int		i;
	t_vec3	c;

	c = mul(scene->ambiant, scene->ambiant_r);
	i = 0;
	while (i < scene->st.nlights)
	{
		add(c, col(scene, hit, i));
		i++;
	}
	return (c);
}
