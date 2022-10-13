#include "minirt.h"

void	set_identity(t_mat4 *mat)
{
	mat->x = (t_vec4) {1, 0, 0, 0};
	mat->y = (t_vec4) {0, 1, 0, 0};
	mat->z = (t_vec4) {0, 0, 1, 0};
	mat->w = (t_vec4) {0, 0, 0, 1};
}

void	set_rotation(t_mat4	*mat, t_vec3 v1, t_vec3 v2)
{	
	t_vec3	axis;
	float	cosA;
	float	k;

	set_identity(mat);
	axis = cross(v1, v2);
	cosA = dot(v1, v2);
	if (1 + cosA < 1e-6)
		return ;
	k = 1 / (1 + cosA);
	mat.x.x = axis.x * axis.x * k + cosA;
	mat.x.y = axis.y * axis.x * k - axis.z;
	mat.x.z = axis.z * axis.x * k - axis.y;
	mat.y.x = axis.x * axis.y * k + axis.z;
	mat.y.y = axis.y * axis.y * k + cosA;
	mat.y.z = axis.z * axis.y * k - axis.x;
	mat.z.x = axis.x * axis.z * k - axis.y;
	mat.z.y = axis.y * axis.z * k + axis.x;
	mat.z.z = axis.z * axis.z * k + cosA;
}

void	set_translation(t_mat4 *mat, t_vec3 coord)
{
	(void) mat;
	(void) coord;
}

void	set_scale(t_mat4 *mat, float height, float radius)
{
	(void) height;
	(void) radius;
}
