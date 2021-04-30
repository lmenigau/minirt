#include "minirt.h"
#include <math.h>

t_vec3	camray(t_global *global, t_ivec coord)
{
	t_ivec	reso;
	t_cam	cam;
	t_vec3	dir;

	reso = global->parse.scene.reso;
	cam = global->parse.scene.st.cams[global->cam];
	dir.x = (2 * (coord.x + 0.5) / (float)reso.x - 1) * global->ratio
		* cam.scale;
	dir.y = (1 - 2 * (coord.y + 0.5) / (float)reso.y) * cam.scale;
	dir.z = -1;
	dir = norm(transform(cam.mat, dir));
	return (dir);
}


float	sphere_solver(t_sphere sp, t_ray ray)
{
	float	delta;
	t_vec3	oc;
	t_vec2	inter;
	t_vec3	v;

	oc = sub(ray.ori, sp.coord);
	v = (t_vec3){dot(ray.dir, ray.dir), 2 * dot(ray.dir, oc),
		dot(oc, oc) - sp.size * sp.size};
	delta = v.y * v.y - 4 * v.x * v.z;
	if (delta >= 0)
	{
		inter.x = -dot(ray.dir, oc) + sqrtf(delta);
		inter.y = -dot(ray.dir, oc) - sqrtf(delta);
		if (inter.x < 0 && inter.y > inter.x)
			return (inter.y);
		else
			return (inter.x);
	}
	return (-1);
}

_Bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit)
{
	float	d;

	d = sphere_solver(sp, ray);
	if (d < 0)
		return (1);
	hit->p = add(ray.ori, mul(ray.dir, d));
	hit->n = norm(sub(hit->p, sp.coord));
	hit->c = sp.color; 
	return (0);
}

t_vec3	intersect(t_global *global, t_ray ray)
{
	int		i;
	t_store	st;
	t_hit	hit;

	i = 0;
	st = global->parse.scene.st;
	while (i < st.nspheres && hit_sphere(st.spheres[i], ray, &hit))
		i++;
	if (i != st.nspheres)
		return (light(&global->parse.scene, hit));
	return ((t_vec3){});
}

t_color	render(t_global *global, t_ivec coord)
{
	t_ray	ray;
	t_vec3	col;

	ray.dir = camray(global, coord);
	ray.ori = global->parse.scene.st.cams[global->cam].ori;
	col = intersect(global, ray);
	return ((t_color){col.x, col.y, col.z});
}
