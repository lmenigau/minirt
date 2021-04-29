#include "minirt.h"
#include <math.h>

t_vec3	camray(t_global *global, t_ivec coord)
{
	t_ivec	reso;
	t_cam	cam;
	t_vec3 	dir;

	reso = global->parse.scene.reso;
	cam = global->parse.scene.st.cams[global->cam];
	dir.x = (2 * (coord.x + 0.5) / (float)reso.x - 1) * global->ratio *
		cam.scale;
	dir.y = (1 - 2 * (coord.y + 0.5) / (float)reso.y) * cam.scale;
	dir.z = -1;
	dir = norm(transform(cam.mat, dir));
	return (dir);
}

void	swap(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}

_Bool	intersect_sphere(t_sphere sp, t_ray ray, float *d)
{
	float	delta;
	t_vec3	oc;
	t_vec2	inter;
	//t_vec3	abc;
	
	oc = sub(ray.ori, sp.coord);
//	abc = (t_vec3){
//		dot(ray.dir, ray.dir),
//		2 * dot(ray.dir, oc),
//		dot(oc, oc) - sp.size * sp.size
//	}; 
	delta = powf(dot(ray.dir, oc), 2) - dot(oc, oc) - powf(sp.size, 2);
	if (delta < 0)
		return (1);
	else
	{
		inter.x = -dot(ray.dir, oc) + sqrtf(delta);
		inter.y = -dot(ray.dir, oc) - sqrtf(delta);
		if (inter.x > inter.y)
			swap(&inter.x, &inter.y);
		if (inter.x < 0)
		{
			*d = inter.y;
			if (inter.y < 0)
				return (1);
		}
	}
	return (0);
}

t_vec3 intersect(t_global *global, t_ray ray)
{
	int		i;
	t_store	st;
	float	d;

	i = 0;
	d = -1;
	st = global->parse.scene.st;
	while (i < st.nspheres && intersect_sphere(st.spheres[i], ray, &d))
			i++;
	if (d > 0)
		return (st.spheres[i].color);
	return((t_vec3){});
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
