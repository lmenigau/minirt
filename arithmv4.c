/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmv4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:52:09 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:52:10 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_vec4	sub4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w});
}

t_vec4	mul4(t_vec4 vec, double b)
{
	return ((t_vec4){vec.x * b, vec.y * b, vec.z * b, vec.w * b});
}

t_vec4	transform4(t_mat4 mat, t_vec4 v)
{
	return ((t_vec4){
		v.x * mat.x.x + v.y * mat.x.y + v.z * mat.x.z + v.w * mat.x.w,
		v.x * mat.y.x + v.y * mat.y.y + v.z * mat.y.z + v.w * mat.y.w,
		v.x * mat.z.x + v.y * mat.z.y + v.z * mat.z.z + v.w * mat.z.w,
		v.x * mat.w.x + v.y * mat.w.y + v.z * mat.w.z + v.w * mat.w.w
	});
}
