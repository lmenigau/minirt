/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:18 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:18 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inv_col1_rows(t_mat4 *m, t_mat4 *id)
{
	if ((*m).x.y != 0)
	{
		if ((*m).y.y != 0)
		{
			(*id).x = sub4((*id).x, mul4((*id).y, (*m).x.y / (*m).y.y));
			(*m).x = sub4((*m).x, mul4((*m).y, (*m).x.y / (*m).y.y));
		}
	}
	if ((*m).x.z != 0)
	{
		if ((*m).z.z != 0)
		{
			(*id).x = sub4((*id).x, mul4((*id).z, (*m).x.z / (*m).z.z));
			(*m).x = sub4((*m).x, mul4((*m).z, (*m).x.z / (*m).z.z));
		}
	}
	if ((*m).x.w != 0)
	{
		if ((*m).w.w != 0)
		{
			(*id).x = sub4((*id).x, mul4((*id).w, (*m).x.w / (*m).w.w));
			(*m).x = sub4((*m).x, mul4((*m).w, (*m).x.w / (*m).w.w));
		}
	}
}

void	inv_col2_rows(t_mat4 *m, t_mat4 *id)
{
	if ((*m).y.z != 0)
	{
		if ((*m).z.z != 0)
		{
			(*id).y = sub4((*id).y, mul4((*id).z, (*m).y.z / (*m).z.z));
			(*m).y = sub4((*m).y, mul4((*m).z, (*m).y.z / (*m).z.z));
		}
	}
	if ((*m).y.w != 0)
	{
		if ((*m).w.w != 0)
		{
			(*id).y = sub4((*id).y, mul4((*id).w, (*m).y.w / (*m).w.w));
			(*m).y = sub4((*m).y, mul4((*m).w, (*m).y.w / (*m).w.w));
		}
	}
}
