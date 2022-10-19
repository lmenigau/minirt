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

// t_mat4	mat4inv(t_mat4 m)
// {
// 	t_mat4	id;

// 	set_identity(&id);

// 	id.x = mul4(id.x, 1 / m.x.x);
// 	m.x = mul4(m.x, 1 / m.x.x);

// 	id.y = sub4(id.y, mul4(id.x, m.y.x));
// 	m.y = sub4(m.y, mul4(m.x, m.y.x));
// 	id.z = sub4(id.z, mul4(id.x, m.z.x));
// 	m.z = sub4(m.z, mul4(m.x, m.z.x));
// 	id.w = sub4(id.w, mul4(id.x, m.w.x));
// 	m.w = sub4(m.w, mul4(m.x, m.w.x));

// 	id.y = mul4(id.y, 1 / m.y.y);
// 	m.y = mul4(m.y, 1 / m.y.y);

// 	id.x = sub4(id.x, mul4(id.y, m.x.y));
// 	m.x = sub4(m.x, mul4(m.y, m.x.y));
// 	id.z = sub4(id.z, mul4(id.y, m.z.y));
// 	m.z = sub4(m.z, mul4(m.y, m.z.y));
// 	id.w = sub4(id.w, mul4(id.y, m.w.y));
// 	m.w = sub4(m.w, mul4(m.y, m.w.y));

// 	id.z = mul4(id.z, 1 / m.z.z);
// 	m.z = mul4(m.z, 1 / m.z.z);

// 	id.x = sub4(id.x, mul4(id.z, m.x.z));
// 	m.x = sub4(m.x, mul4(m.z, m.x.z));
// 	id.y = sub4(id.y, mul4(id.z, m.y.z));
// 	m.y = sub4(m.y, mul4(m.z, m.y.z));
// 	id.w = sub4(id.w, mul4(id.z, m.w.z));
// 	m.w = sub4(m.w, mul4(m.z, m.w.z));

// 	id.w = mul4(id.w, 1 / m.w.w);
// 	m.w = mul4(m.w, 1 / m.w.w);

// 	id.x = sub4(id.x, mul4(id.w, m.x.w));
// 	m.x = sub4(m.x, mul4(m.w, m.x.w));
// 	id.y = sub4(id.y, mul4(id.w, m.y.w));
// 	m.y = sub4(m.y, mul4(m.w, m.y.w));
// 	id.z = sub4(id.z, mul4(id.w, m.z.w));
// 	m.z = sub4(m.z, mul4(m.w, m.z.w));
// 	return (id);
// }

int	is_close(float n1, float n2)
{
	if (n1 > n2 && n1 - n2 < 1e-6 && n1 - n2 > -1e-6)
		return (1);
	if (n2 > n1 && n2 - n1 < 1e-6 && n2 - n1 > -1e-6)
		return (1);
	return (0);
}

void	swap_rows(t_vec4 *r1, t_vec4 *r2)
{
	t_vec4 temp;

	temp = *r1;
	*r1 = *r2;
	*r2 = temp;
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

t_mat4	mat4inv(t_mat4 m)
{
	t_mat4	id;
	int		i;
	printmat4(m);
	set_identity(&id);

	i = 0;
	while (!is_identity(m) && i < 200)
	{
		//col 1
		if (m.x.x < m.y.x)
		{
			swap_rows(&m.x, &m.y);
			swap_rows(&id.x, &id.y);
		}
		if (m.x.x < m.z.x)
		{
			swap_rows(&m.x, &m.z);
			swap_rows(&id.x, &id.z);
		}
		if (m.x.x < m.w.x)
		{
			swap_rows(&m.x, &m.w);
			swap_rows(&id.x, &id.w);
		}
		if (m.x.x == 0)
			m.x.x = 1e-6;
		id.x = mul4(id.x, 1 / m.x.x);
		m.x = mul4(m.x, 1 / m.x.x);
		if (m.y.x != 0)
		{
			id.y = sub4(id.y, mul4(id.x, m.y.x));
			m.y = sub4(m.y, mul4(m.x, m.y.x));
		}
		if (m.z.x != 0)
		{
			id.z = sub4(id.z, mul4(id.x, m.z.x));
			m.z = sub4(m.z, mul4(m.x, m.z.x));
		}
		if (m.w.x != 0)
		{
			id.w = sub4(id.w, mul4(id.x, m.w.x));
			m.w = sub4(m.w, mul4(m.x, m.w.x));
		}
		if (m.x.y != 0)
		{
			if (m.y.y != 0)
			{
				id.x = sub4(id.x, mul4(id.y, m.x.y / m.y.y));
				m.x = sub4(m.x, mul4(m.y, m.x.y / m.y.y));
			}
		}
		if (m.x.z != 0)
		{
			if (m.z.z != 0)
			{
				id.x = sub4(id.x, mul4(id.z, m.x.z / m.z.z));
				m.x = sub4(m.x, mul4(m.z, m.x.z / m.z.z));
			}
		}
		if (m.x.w != 0)
		{
			if (m.w.w != 0)
			{
				id.x = sub4(id.x, mul4(id.w, m.x.w / m.w.w));
				m.x = sub4(m.x, mul4(m.w, m.x.w / m.w.w));
			}
		}
		// col2
		if (m.y.y < m.x.y)
		{
			swap_rows(&m.y, &m.x);
			swap_rows(&id.y, &id.x);
		}
		if (m.y.y < m.z.y)
		{
			swap_rows(&m.y, &m.z);
			swap_rows(&id.y, &id.z);
		}
		if (m.y.y < m.w.y)
		{
			swap_rows(&m.y, &m.w);
			swap_rows(&id.y, &id.w);
		}
		if (m.y.y == 0)
			m.y.y = 1e-6;
		id.y = mul4(id.y, 1 / m.y.y);
		m.y = mul4(m.y, 1 / m.y.y);
		if (m.z.y != 0)
		{
			id.z = sub4(id.z, mul4(id.y, m.z.y));
			m.z = sub4(m.z, mul4(m.y, m.z.y));
		}
		if (m.w.y != 0)
		{
			id.w = sub4(id.w, mul4(id.y, m.w.y));
			m.w = sub4(m.w, mul4(m.y, m.w.y));
		}
		if (m.y.z != 0)
		{
			if (m.z.z != 0)
			{
				id.y = sub4(id.y, mul4(id.z, m.y.z / m.z.z));
				m.y = sub4(m.y, mul4(m.z, m.y.z / m.z.z));
			}
		}
		if (m.y.w != 0)
		{
			if (m.w.w != 0)
			{
				id.y = sub4(id.y, mul4(id.w, m.y.w / m.w.w));
				m.y = sub4(m.y, mul4(m.w, m.y.w / m.w.w));
			}
		}
	// col 3
		if (m.z.z < m.x.z)
		{
			swap_rows(&m.z, &m.x);
			swap_rows(&id.z, &id.x);
		}
		if (m.z.z < m.y.z)
		{
			swap_rows(&m.z, &m.y);
			swap_rows(&id.z, &id.y);
		}
		if (m.z.z < m.w.z)
		{
			swap_rows(&m.z, &m.w);
			swap_rows(&id.z, &id.w);
		}
		if (m.z.z == 0)
			m.z.z = 1e-6;
		id.z = mul4(id.z, 1 / m.z.z);
		m.z = mul4(m.z, 1 / m.z.z);
		if (m.w.z != 0)
		{
			id.w = sub4(id.w, mul4(id.z, m.w.z));
			m.w = sub4(m.w, mul4(m.z, m.w.z));
		}
		if (m.z.w != 0)
		{
			if (m.w.w != 0)
			{
				id.z = sub4(id.z, mul4(id.w, m.z.w / m.w.w));
				m.z = sub4(m.z, mul4(m.w, m.z.w / m.w.w));
			}
		}
	// col 4
		if (m.w.w < m.x.w)
		{
			swap_rows(&m.w, &m.x);
			swap_rows(&id.w, &id.x);
		}
		if (m.w.w < m.y.w)
		{
			swap_rows(&m.w, &m.y);
			swap_rows(&id.w, &id.y);
		}
		if (m.w.w < m.z.w)
		{
			swap_rows(&m.w, &m.z);
			swap_rows(&id.w, &id.z);
		}
		if (m.w.w == 0)
			m.w.w = 1e-6;
		id.w = mul4(id.w, 1 / m.w.w);
		m.w = mul4(m.w, 1 / m.w.w);
		i++;
	}
	printf("nb rows: %d\n", i);
	printmat4(m);
	return (id);
}
