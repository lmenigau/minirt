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

t_vec3	intersect(t_global *global, t_ray ray)
{
	int		i;
	t_store	st;
	t_hit	hit;

	st = global->parse.scene.st;
	hit = (t_hit){.d = INFINITY};
	i = 0;
	while (i < st.nplanes)
	{
		hit_plane(st.planes[i], ray, &hit);
		i++;
	}
	i = 0;
	while (i < st.nspheres)
	{
		hit_sphere(st.spheres[i], ray, &hit);
		i++;
	}
	if (hit.d > 0)
		return (light(&global->parse.scene, hit));
	return (0);
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
