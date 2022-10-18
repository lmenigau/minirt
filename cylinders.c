#include "minirt.h"

int	set_inter(t_vec2 *inter, t_ray ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;

	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * (ray.ori.x * ray.dir.x + ray.ori.y * ray.dir.y);
	c = ray.ori.x * ray.ori.x + ray.ori.y * ray.ori.y - 1;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		(*inter).x = (-b + sqrtf(delta)) / (2 * a);
		(*inter).y = (-b - sqrtf(delta)) / (2 * a);
		return (0);
	}
	return (1);
}

float	cyl_solver(t_ray ray)
{
	t_vec2	inter;
	float	z;

	if (set_inter(&inter, ray) == 1)
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

float	caps_solver(t_ray ray)
{
	t_vec2	inter;
	float	x;
	float	y;
	t_plane	pl;

	pl.coord = (t_vec3){0, 0, 1};
	pl.ori = (t_vec3){0, 0, 1};
	inter.x = plane_solver(pl, ray);
	pl.coord.z = -1;
	inter.y = plane_solver(pl, ray);
	if (inter.x > 0 && (inter.y < 0 || inter.x < inter.y))
	{
		x = ray.ori.x + inter.x * ray.dir.x;
		y = ray.ori.y + inter.x * ray.dir.y;
		if (x * x + y * y <= 1)
			return (inter.x);
	}
	else if (inter.y > 0 && (inter.x < 0 || inter.y < inter.x))
	{
		x = ray.ori.x + inter.y * ray.dir.x;
		y = ray.ori.y + inter.y * ray.dir.y;
		if (x * x + y * y <= 1)
			return (inter.y);
	}
	return (-1);
}


t_ray	set_locray(t_cyl cy, t_ray ray)
{
	t_vec4	local_p1;
	t_vec4	local_p2;
	t_ray	loc_ray;

	local_p1 = (t_vec4){ray.ori.x, ray.ori.y, ray.ori.z, 1};
	local_p1 = transform4(cy.inv_mat, local_p1);
	local_p2 = (t_vec4){ray.ori.x + ray.dir.x,
		ray.ori.y + ray.dir.y,
		ray.ori.z + ray.dir.z,
		1};
	local_p2 = transform4(cy.inv_mat, local_p2);
	loc_ray.ori = (t_vec3){local_p1.x, local_p1.y, local_p1.z};
	loc_ray.dir = norm((t_vec3){local_p2.x - local_p1.x,
			local_p2.y - local_p1.y,
			local_p2.z - local_p1.z});
	return (loc_ray);

}

void	hit_cyl(t_cyl cy, t_ray ray, t_hit *hit)
{
	float	d1;
	float	d2;
	t_ray	loc_ray;

	// loc_ray = set_locray(cy, ray);
	loc_ray = ray;
	d1 = cyl_solver(loc_ray);
	d2 = caps_solver(loc_ray);
	if (d1 > 0 && (d2 < 0 || d1 < d2))
	{
		hit->d = d1;
		hit->p = add(loc_ray.ori, mul(loc_ray.dir, d1));
		hit->n = norm(sub(hit->p, (t_vec3){0, 0, hit->p.z}));
		hit->c = cy.color;
	}
	else if (d2 > 0 && (d1 < 0 || d2 < d1))
	{
		hit->d = d2;
		hit->p = add(loc_ray.ori, mul(loc_ray.dir, d2));
		hit->n = (t_vec3){0, 0, -1};
		hit->c = cy.color;
	}
}
