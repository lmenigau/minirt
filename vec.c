#include "minirt.h"
#include <math.h>

float	len(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	norm(t_vec3 vec)
{
	float	invsq;

	invsq = 1 / len(vec);
	return ((t_vec3){vec.x * invsq, vec.y * invsq, vec.z * invsq});
}

t_vec3	mul(t_vec3 vec, float b)
{
	return ((t_vec3){vec.x * b, vec.y * b, vec.z * b});
}

t_vec4	mul4(t_vec4 vec, float b)
{
	return ((t_vec4){vec.x * b, vec.y * b, vec.z * b, vec.w * b});
}

float	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec4	sub4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w});
}

t_vec3	vmul(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_vec3	add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

t_vec3	transform(t_mat mat, t_vec3 v)
{
	return ((t_vec3){
		v.x * mat.r.x + v.y * mat.u.x + v.z * mat.f.x,
		v.x * mat.r.y + v.y * mat.u.y + v.z * mat.f.y,
		v.x * mat.r.z + v.y * mat.u.z + v.z * mat.f.z,
	});
}
t_vec3	clamp(t_vec3 v)
{
	return (t_vec3){fminf(v.x, 1), fminf(v.y, 1), fminf(v.z, 1)};
}

_Bool	is_colinear(t_vec3 v1, t_vec3 v2)
{
	int	k1;
	int	k2;
	int	k3;

	if ((v1.x ==0 && v2.x != 0)
		|| (v1.y ==0 && v2.y != 0)
		|| (v1.y ==0 && v2.y != 0))
		return (0);
	if (v1.x ==0)
		k1 = 0;
	else
		k1 = v2.x / v1.x;
	if (v1.y ==0)
		k2 = 0;
	else
		k2 = v2.y / v1.y;
	if (v1.z ==0)
		k3 = 0;
	else
		k3 = v2.z / v1.z;
	if ((k1 == 0 || k2 == 0 || k1 == k2)
		&& (k1 == 0 || k3 == 0 || k1 == k3)
		&& (k2 == 0 || k3 == 0 || k2 == k3))
		return (1);
	return (0);
}
