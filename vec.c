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


float	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
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
