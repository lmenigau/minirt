#include "minirt.h"
#include <math.h>
#include <stdio.h>

t_vec3	camray(t_global *global, t_ivec coord)
{
	t_ivec	reso;
	t_cam	cam;
	t_vec3	dir;

	reso = global->parse.scene.reso;
	cam = global->parse.scene.st.cams[global->cam];
	dir.x = (2 * (coord.x + 0.5) / (float)reso.x - 1) * cam.scale;
	dir.y = (1 - 2 * (coord.y + 0.5) / (float)reso.y) * global->ratio * cam.scale;
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

_Bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit)
{
	float	d;
	t_vec3	v;

	d = sphere_solver(sp, ray);
	if (d < 0)
		return (0);
	v = add(ray.ori, mul(ray.dir, d));
	if (len(sub(hit->p, ray.ori)) == 0
		|| len(sub(v, ray.ori)) < len(sub(hit->p, ray.ori)))
	{
		hit->p = v;
		hit->n = norm(sub(hit->p, sp.coord));
		hit->c = sp.color;
	}
	return (1);
}

t_vec3	intersect(t_global *global, t_ray ray)
{
	int		i;
	t_store	st;
	t_hit	hit;

	i = 0;
	st = global->parse.scene.st;
	hit.c = (t_vec3){};
	hit.p = ray.ori;
	while (i < st.nspheres)
	{
		hit_sphere(st.spheres[i], ray, &hit);
		i++;
	}
	i = 0;
	while (i < st.nplanes)
	{
		hit_plane(st.planes[i], ray, &hit);
		i++;
	}
	return (light(&global->parse.scene, hit));
	return (hit.c);
}

t_color	render(t_global *global, t_ivec coord)
{
	t_ray	ray;
	t_vec3	col;

	ray.dir = camray(global, coord);
	ray.ori = global->parse.scene.st.cams[global->cam].coord;
	col = intersect(global, ray);
	return ((t_color){col.x * 255, col.y * 255, col.z * 255});
}
