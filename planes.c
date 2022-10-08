#include "minirt.h"

float	plane_solver(t_plane pl, t_ray ray)
{
	t_vec3	op;
	float	inter;

	op = pl.coord - ray.ori;
	inter = dot(op, pl.ori) / dot(ray.dir, pl.ori);
	return (inter);
}

int	hit_plane(t_plane pl, t_ray ray, t_hit *hit)
{
	float	d;
	t_vec3	v;

	d = plane_solver(pl, ray);
	if (d < 0)
		return (0);
	v = ray.ori + ray.dir * d;
	if (len(hit->p - ray.ori) == 0
		|| len(v - ray.ori) < len(hit->p - ray.ori))
	{
		hit->p = v;
		hit->n = pl.ori;
		hit->c = pl.color;
	}
	return (1);
}
