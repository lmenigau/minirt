/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:12 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:13 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	printmat4(t_mat4 m)
{
	printf("%f\t%f\t%f\t%f\n", m.x.x, m.x.y, m.x.z, m.x.w);
	printf("%f\t%f\t%f\t%f\n", m.y.x, m.y.y, m.y.z, m.y.w);
	printf("%f\t%f\t%f\t%f\n", m.z.x, m.z.y, m.z.z, m.z.w);
	printf("%f\t%f\t%f\t%f\n", m.w.x, m.w.y, m.w.z, m.w.w);
}

void	mat4mul_zw(t_mat4 (*new_map), t_mat4 m1, t_mat4 m2)
{
	(*new_map).z.x = m1.z.x * m2.x.x + m1.z.y * m2.y.x + m1.z.z * m2.z.x
		+ m1.z.w * m2.w.x;
	(*new_map).z.y = m1.z.x * m2.x.y + m1.z.y * m2.y.y + m1.z.z * m2.z.y
		+ m1.z.w * m2.w.y;
	(*new_map).z.z = m1.z.x * m2.x.z + m1.z.y * m2.y.z + m1.z.z * m2.z.z
		+ m1.z.w * m2.w.z;
	(*new_map).z.w = m1.z.x * m2.x.w + m1.z.y * m2.y.w + m1.z.z * m2.z.w
		+ m1.z.w * m2.w.w;
	(*new_map).w.x = m1.w.x * m2.x.x + m1.w.y * m2.y.x + m1.w.z * m2.z.x
		+ m1.w.w * m2.w.x;
	(*new_map).w.y = m1.w.x * m2.x.y + m1.w.y * m2.y.y + m1.w.z * m2.z.y
		+ m1.w.w * m2.w.y;
	(*new_map).w.z = m1.w.x * m2.x.z + m1.w.y * m2.y.z + m1.w.z * m2.z.z
		+ m1.w.w * m2.w.z;
	(*new_map).w.w = m1.w.x * m2.x.w + m1.w.y * m2.y.w + m1.w.z * m2.z.w
		+ m1.w.w * m2.w.w;
}

t_mat4	mat4mul(t_mat4 m1, t_mat4 m2)
{
	t_mat4	new_mat;

	new_mat.x.x = m1.x.x * m2.x.x + m1.x.y * m2.y.x + m1.x.z * m2.z.x
		+ m1.x.w * m2.w.x;
	new_mat.x.y = m1.x.x * m2.x.y + m1.x.y * m2.y.y + m1.x.z * m2.z.y
		+ m1.x.w * m2.w.y;
	new_mat.x.z = m1.x.x * m2.x.z + m1.x.y * m2.y.z + m1.x.z * m2.z.z
		+ m1.x.w * m2.w.z;
	new_mat.x.w = m1.x.x * m2.x.w + m1.x.y * m2.y.w + m1.x.z * m2.z.w
		+ m1.x.w * m2.w.w;
	new_mat.y.x = m1.y.x * m2.x.x + m1.y.y * m2.y.x + m1.y.z * m2.z.x
		+ m1.y.w * m2.w.x;
	new_mat.y.y = m1.y.x * m2.x.y + m1.y.y * m2.y.y + m1.y.z * m2.z.y
		+ m1.y.w * m2.w.y;
	new_mat.y.z = m1.y.x * m2.x.z + m1.y.y * m2.y.z + m1.y.z * m2.z.z
		+ m1.y.w * m2.w.z;
	new_mat.y.w = m1.y.x * m2.x.w + m1.y.y * m2.y.w + m1.y.z * m2.z.w
		+ m1.y.w * m2.w.w;
	mat4mul_zw(&new_mat, m1, m2);
	return (new_mat);
}

int	is_close(float n1, float n2)
{
	if (n1 > n2 && n1 - n2 < 10e-6 && n1 - n2 > -10e-6)
		return (1);
	if (n2 >= n1 && n2 - n1 < 10e-6 && n2 - n1 > -10e-6)
		return (1);
	return (0);
}

int	is_identity(t_mat4 m)
{
	if (!is_close(m.x.x, 1) || !is_close(m.y.y, 1)
		|| !is_close(m.z.z, 1) || !is_close(m.w.w, 1))
		return (0);
	if (!is_close(m.x.x + m.x.y + m.x.z + m.x.w, 1)
		|| !is_close(m.y.x + m.y.y + m.y.z + m.y.w, 1)
		|| !is_close(m.z.x + m.z.y + m.z.z + m.z.w, 1)
		|| !is_close (m.w.x + m.w.y + m.w.z + m.w.w, 1))
		return (0);
	return (1);
}
