#include "minirt.h"

int	set_inter(t_vec2 *inter, t_cyl cy, t_ray ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;

	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * (ray.ori.x * ray.dir.x + ray.ori.y * ray.dir.y);
	c = ray.ori.x * ray.ori.x + ray.ori.y * ray.ori.y - cy.radius * cy.radius;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		(*inter).x = (-b + sqrtf(delta)) / (2 * a);
		(*inter).y = (-b - sqrtf(delta)) / (2 * a);
		return (0);
	}
	return (1);
}

float	cyl_solver(t_cyl cy, t_ray ray)
{
	t_vec2	inter;
	float	z;

	if (set_inter(&inter, cy, ray) == 1)
		return (-1);
	if (inter.x > 0 && (inter.y < 0 || inter.x < inter.y))
	{
		z = ray.ori.z + inter.x * ray.dir.z;
		if (z >= -1 && z <= 1)
			return (inter.x);
	}
	else if (inter.y > 0 && (inter.x < 0 || inter.y < inter.x))
	{
		z = ray.ori.z + inter.y * ray.dir.z;
		if (z >= -1 && z <= 1)
			return (inter.y);
	}
	return (-1);
}

_Bool	hit_cyl(t_cyl cy, t_ray ray, t_hit *hit)
{
	float	d;
	t_vec3	v;

// transform ray
	d = cyl_solver(cy, ray);
	// if (d < 0)
	// 	d = caps_solver(cy, ray);
	if (d < 0)
		return (-1);
	v = add(ray.ori, mul(ray.dir, d)); // transform v
	if (len(sub(hit->p, ray.ori)) == 0
		|| len(sub(v, ray.ori)) < len(sub(hit->p, ray.ori)))
	{
		hit->p = v;
		hit->n = norm(sub((t_vec3){0, 0, v.z}, v));
		hit->c = cy.color;
	}
	return (0);
}
