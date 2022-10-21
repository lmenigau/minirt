/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:20 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:21 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_vec3	set_worldpoint(t_cyl cy, t_vec3 loc_v)
{
	t_vec3	v;
	t_vec4	loc_v4;

	loc_v4 = (t_vec4){loc_v.x, loc_v.y, loc_v.z, 1};
	loc_v4 = transform4(cy.mat, loc_v4);
	v = (t_vec3){loc_v4.x, loc_v4.y, loc_v4.z};
	return (v);
}

void	hit_cyl(t_cyl cy, t_ray ray, t_hit *hit)
{
	t_vec2	d;
	t_ray	loc_ray;

	loc_ray = set_locray(cy, ray);
	d.x = cyl_solver(loc_ray);
	d.y = caps_solver(loc_ray);
	if (cyl_inter(d, cy, ray, hit) == 0)
		caps_inter(d, cy, ray, hit);
}
