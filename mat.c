#include "minirt.h"

void	printmat4(t_mat4 m)
{
	printf("%f\t%f\t%f\t%f\n", m.x.x, m.x.y, m.x.z, m.x.w);
	printf("%f\t%f\t%f\t%f\n", m.y.x, m.y.y, m.y.z, m.y.w);
	printf("%f\t%f\t%f\t%f\n", m.z.x, m.z.y, m.z.z, m.z.w);
	printf("%f\t%f\t%f\t%f\n", m.w.x, m.w.y, m.w.z, m.w.w);
}

t_mat4	mat4mul(t_mat4 m1, t_mat4 m2)
{
	t_mat4	new_mat;

	new_mat.x.x = m1.x.x * m2.x.x + m1.x.y * m2.y.x + m1.x.z * m2.z.x + m1.x.w * m2.w.x;
	new_mat.x.y = m1.x.x * m2.x.y + m1.x.y * m2.y.y + m1.x.z * m2.z.y + m1.x.w * m2.w.y;
	new_mat.x.z = m1.x.x * m2.x.z + m1.x.y * m2.y.z + m1.x.z * m2.z.z + m1.x.w * m2.w.z;
	new_mat.x.w = m1.x.x * m2.x.w + m1.x.y * m2.y.w + m1.x.z * m2.z.w + m1.x.w * m2.w.w;

	new_mat.y.x = m1.y.x * m2.x.x + m1.y.y * m2.y.x + m1.y.z * m2.z.x + m1.y.w * m2.w.x;
	new_mat.y.y = m1.y.x * m2.x.y + m1.y.y * m2.y.y + m1.y.z * m2.z.y + m1.y.w * m2.w.y;
	new_mat.y.z = m1.y.x * m2.x.z + m1.y.y * m2.y.z + m1.y.z * m2.z.z + m1.y.w * m2.w.z;
	new_mat.y.w = m1.y.x * m2.x.w + m1.y.y * m2.y.w + m1.y.z * m2.z.w + m1.y.w * m2.w.w;

	new_mat.z.x = m1.z.x * m2.x.x + m1.z.y * m2.y.x + m1.z.z * m2.z.x + m1.z.w * m2.w.x;
	new_mat.z.y = m1.z.x * m2.x.y + m1.z.y * m2.y.y + m1.z.z * m2.z.y + m1.z.w * m2.w.y;
	new_mat.z.z = m1.z.x * m2.x.z + m1.z.y * m2.y.z + m1.z.z * m2.z.z + m1.z.w * m2.w.z;
	new_mat.z.w = m1.z.x * m2.x.w + m1.z.y * m2.y.w + m1.z.z * m2.z.w + m1.z.w * m2.w.w;

	new_mat.w.x = m1.w.x * m2.x.x + m1.w.y * m2.y.x + m1.w.z * m2.z.x + m1.w.w * m2.w.x;
	new_mat.w.y = m1.w.x * m2.x.y + m1.w.y * m2.y.y + m1.w.z * m2.z.y + m1.w.w * m2.w.y;
	new_mat.w.z = m1.w.x * m2.x.z + m1.w.y * m2.y.z + m1.w.z * m2.z.z + m1.w.w * m2.w.z;
	new_mat.w.w = m1.w.x * m2.x.w + m1.w.y * m2.y.w + m1.w.z * m2.z.w + m1.w.w * m2.w.w;
	return (new_mat);
}

// Using Gauss Jordan Elimination
// https://www.intmath.com/matrices-determinants/inverse-matrix-gauss-jordan-elimination.php

t_mat4	mat4inv(t_mat4 m)
{
	t_mat4	id;

	set_identity(&id);

	id.x = mul4(id.x, 1 / m.x.x);
	m.x = mul4(m.x, 1 / m.x.x);

	id.y = sub4(id.y, mul4(id.x, m.y.x));
	m.y = sub4(m.y, mul4(m.x, m.y.x));
	id.z = sub4(id.z, mul4(id.x, m.z.x));
	m.z = sub4(m.z, mul4(m.x, m.z.x));
	id.w = sub4(id.w, mul4(id.x, m.w.x));
	m.w = sub4(m.w, mul4(m.x, m.w.x));

	id.y = mul4(id.y, 1 / m.y.y);
	m.y = mul4(m.y, 1 / m.y.y);

	id.x = sub4(id.x, mul4(id.y, m.x.y));
	m.x = sub4(m.x, mul4(m.y, m.x.y));
	id.z = sub4(id.z, mul4(id.y, m.z.y));
	m.z = sub4(m.z, mul4(m.y, m.z.y));
	id.w = sub4(id.w, mul4(id.y, m.w.y));
	m.w = sub4(m.w, mul4(m.y, m.w.y));

	id.z = mul4(id.z, 1 / m.z.z);
	m.z = mul4(m.z, 1 / m.z.z);

	id.x = sub4(id.x, mul4(id.z, m.x.z));
	m.x = sub4(m.x, mul4(m.z, m.x.z));
	id.y = sub4(id.y, mul4(id.z, m.y.z));
	m.y = sub4(m.y, mul4(m.z, m.y.z));
	id.w = sub4(id.w, mul4(id.z, m.w.z));
	m.w = sub4(m.w, mul4(m.z, m.w.z));

	id.w = mul4(id.w, 1 / m.w.w);
	m.w = mul4(m.w, 1 / m.w.w);

	id.x = sub4(id.x, mul4(id.w, m.x.w));
	m.x = sub4(m.x, mul4(m.w, m.x.w));
	id.y = sub4(id.y, mul4(id.w, m.y.w));
	m.y = sub4(m.y, mul4(m.w, m.y.w));
	id.z = sub4(id.z, mul4(id.w, m.z.w));
	m.z = sub4(m.z, mul4(m.w, m.z.w));
	return (id);
}
