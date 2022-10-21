/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:02 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:03 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

_Bool	is_colinear(t_vec3 v1, t_vec3 v2)
{
	int	k1;
	int	k2;
	int	k3;

	if ((v1.x == 0 && v2.x != 0)
		|| (v1.y == 0 && v2.y != 0)
		|| (v1.y == 0 && v2.y != 0))
		return (0);
	if (v1.x == 0)
		k1 = 0;
	else
		k1 = v2.x / v1.x;
	if (v1.y == 0)
		k2 = 0;
	else
		k2 = v2.y / v1.y;
	if (v1.z == 0)
		k3 = 0;
	else
		k3 = v2.z / v1.z;
	if ((k1 == 0 || k2 == 0 || k1 == k2)
		&& (k1 == 0 || k3 == 0 || k1 == k3)
		&& (k2 == 0 || k3 == 0 || k2 == k3))
		return (1);
	return (0);
}

void	set_identity(t_mat4 *mat)
{
	mat->x = (t_vec4){1, 0, 0, 0};
	mat->y = (t_vec4){0, 1, 0, 0};
	mat->z = (t_vec4){0, 0, 1, 0};
	mat->w = (t_vec4){0, 0, 0, 1};
}

//https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724

void	set_rotation(t_mat4	*mat, t_vec3 v1, t_vec3 v2)
{
	t_vec3	axis;
	float	cosa;
	float	k;

	set_identity(mat);
	if (is_colinear(v1, v2))
		return ;
	axis = cross(v1, v2);
	cosa = dot(v1, v2);
	if (1 + cosa < 10e-6)
		return ;
	k = 1 / (1 + cosa);
	mat->x.x = axis.x * axis.x * k + cosa;
	mat->x.y = axis.y * axis.x * k - axis.z;
	mat->x.z = axis.z * axis.x * k + axis.y;
	mat->y.x = axis.x * axis.y * k + axis.z;
	mat->y.y = axis.y * axis.y * k + cosa;
	mat->y.z = axis.z * axis.y * k - axis.x;
	mat->z.x = axis.x * axis.z * k - axis.y;
	mat->z.y = axis.y * axis.z * k + axis.x;
	mat->z.z = axis.z * axis.z * k + cosa;
}

void	set_translation(t_mat4 *mat, t_vec3 coord)
{
	set_identity(mat);
	mat->x.w = coord.x;
	mat->y.w = coord.y;
	mat->z.w = coord.z;
}

void	set_scale(t_mat4 *mat, float x, float y, float z)
{
	set_identity(mat);
	mat->x.x = x;
	mat->y.y = y;
	mat->z.z = z;
}
