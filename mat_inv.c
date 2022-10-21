/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:15 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:16 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inv_col1(t_mat4 *m, t_mat4 *id)
{
	if ((*m).x.x > 1e-6 || (*m).x.x < -1e-6)
	{
		(*id).x = mul4((*id).x, 1 / (*m).x.x);
		(*m).x = mul4((*m).x, 1 / (*m).x.x);
	}
	if ((*m).y.x != 0)
	{
		(*id).y = sub4((*id).y, mul4((*id).x, (*m).y.x));
		(*m).y = sub4((*m).y, mul4((*m).x, (*m).y.x));
	}
	if ((*m).z.x != 0)
	{
		(*id).z = sub4((*id).z, mul4((*id).x, (*m).z.x));
		(*m).z = sub4((*m).z, mul4((*m).x, (*m).z.x));
	}
	if ((*m).w.x != 0)
	{
		(*id).w = sub4((*id).w, mul4((*id).x, (*m).w.x));
		(*m).w = sub4((*m).w, mul4((*m).x, (*m).w.x));
	}
	inv_col1_rows(m, id);
}

void	inv_col2(t_mat4 *m, t_mat4 *id)
{
	if ((*m).y.y > 1e-6 || (*m).y.y < -1e-6)
	{
		(*id).y = mul4((*id).y, 1 / (*m).y.y);
		(*m).y = mul4((*m).y, 1 / (*m).y.y);
	}
	if ((*m).z.y != 0)
	{
		(*id).z = sub4((*id).z, mul4((*id).y, (*m).z.y));
		(*m).z = sub4((*m).z, mul4((*m).y, (*m).z.y));
	}
	if ((*m).w.y != 0)
	{
		(*id).w = sub4((*id).w, mul4((*id).y, (*m).w.y));
		(*m).w = sub4((*m).w, mul4((*m).y, (*m).w.y));
	}
	inv_col2_rows(m, id);
}

void	inv_col3(t_mat4 *m, t_mat4 *id)
{
	if ((*m).z.z > 1e-6 || (*m).z.z < -1e-6)
	{
		(*id).z = mul4((*id).z, 1 / (*m).z.z);
		(*m).z = mul4((*m).z, 1 / (*m).z.z);
	}
	if ((*m).w.z != 0)
	{
		(*id).w = sub4((*id).w, mul4((*id).z, (*m).w.z));
		(*m).w = sub4((*m).w, mul4((*m).z, (*m).w.z));
	}
	if ((*m).z.w != 0)
	{
		if ((*m).w.w != 0)
		{
			(*id).z = sub4((*id).z, mul4((*id).w, (*m).z.w / (*m).w.w));
			(*m).z = sub4((*m).z, mul4((*m).w, (*m).z.w / (*m).w.w));
		}
	}
}

void	inv_col4(t_mat4 *m, t_mat4 *id)
{
	if ((*m).w.w > 1e-6 || (*m).w.w < -1e-6)
	{
		(*id).w = mul4((*id).w, 1 / (*m).w.w);
		(*m).w = mul4((*m).w, 1 / (*m).w.w);
	}
}

t_mat4	mat4inv(t_mat4 m)
{
	t_mat4	id;
	int		i;

	set_identity(&id);
	i = 0;
	while (is_identity(m) == 0 && i < 100)
	{
		inv_col1(&m, &id);
		inv_col2(&m, &id);
		inv_col3(&m, &id);
		inv_col4(&m, &id);
		i++;
	}
	return (id);
}
