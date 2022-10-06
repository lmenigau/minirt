#include "minirt.h"

float	plane_solver(t_plane pl, t_ray ray)
{
	t_vec3	op;
	float	inter;

	op = sub(pl.coord, ray.ori);
	inter = dot(op, pl.ori) / dot(ray.dir, pl.ori);
	return (inter);
}

int	hit_plane(t_plane pl, t_ray ray, t_hit *hit)
{
	float	d;
	t_vec3	v;

	d = plane_solver(pl, ray);
	if (d < 0)
		return (1);
	v = add(ray.ori, mul(ray.dir, d));
	if (len(sub(hit->p, ray.ori)) == 0
		|| len(sub(v, ray.ori)) < len(sub(hit->p, ray.ori)))
	{
		hit->p = v;
		hit->n = pl.ori;
		hit->c = pl.color;
	}
	return (0);
}
