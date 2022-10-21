/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:03:28 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 10:10:29 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stddef.h>

typedef struct s_options
{
	_Bool	save;
}				t_options;

typedef unsigned char	t_uchar;

typedef struct s_ivec
{
	int		x;
	int		y;
}				t_ivec;

typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

__attribute__((ext_vector_type(3)))
typedef float t_vec3;

# if __has_attribute(ext_vector_type)

__attribute__((ext_vector_type(4)))
typedef double t_vec4;
# else

typedef struct s_vec4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4;
# endif

typedef struct s_ray
{
	t_vec3	dir;
	t_vec3	ori;
}				t_ray;

typedef struct s_mat
{
	t_vec3	f;
	t_vec3	r;
	t_vec3	u;
}				t_mat;

typedef struct s_mat4
{
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;
	t_vec4	w;
}				t_mat4;

typedef struct s_color
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;
}				t_color;

typedef struct s_hit
{
	t_vec3		p;
	t_vec3		n;
	t_vec3		c;
	float		d;

}				t_hit;

typedef struct s_light
{
	t_vec3	coord;
	t_vec3	color;
	float	bright;
}				t_light;

typedef struct s_sphere
{
	t_vec3	coord;
	t_vec3	color;
	float	size;
}				t_sphere;

typedef struct s_plane
{
	t_vec3	coord;
	t_vec3	ori;
	t_vec3	color;
}				t_plane;

typedef struct s_tri
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	color;
}				t_tri;

typedef struct s_box
{
	t_vec3	coord;
	t_vec3	ori;
	t_vec3	color;
	float	size;
}				t_box;

typedef struct s_cyl
{
	t_vec3	coord;
	t_vec3	ori;
	t_vec3	color;
	float	radius;
	float	height;
	t_mat4	mat;
	t_mat4	inv_mat;
}				t_cyl;

typedef struct s_cam
{
	t_mat	mat;
	t_vec3	coord;
	t_vec3	ori;
	float	fov;
	float	scale;
}				t_cam;

struct	s_object
{
	t_vec3	coord;
	t_vec3	ori;
	t_vec3	color;
	float	scale;
};

typedef struct s_store
{
	t_cam		*cams;
	int			ncams;
	t_light		*lights;
	int			nlights;
	t_sphere	*spheres;
	int			nspheres;
	t_plane		*planes;
	int			nplanes;
	t_box		*boxs;
	int			nboxs;
	t_cyl		*cyls;
	int			ncyls;
	t_tri		*tris;
	int			ntris;
}				t_store;

typedef struct s_scene
{
	t_ivec	reso;
	float	ambiant_r;
	t_vec3	ambiant;
	t_store	st;
	_Bool	isreso;
	_Bool	isambiant;
	_Bool	islight;
	_Bool	iscam;
}				t_scene;

struct s_buf
{
	size_t	index;
	size_t	len;
	int		fd;
	char	buf[4096];
};

typedef struct s_parse
{
	struct s_buf	buf;
	struct s_scene	scene;
	char			current;
}				t_parse;

typedef struct s_global
{
	t_options		options;
	t_parse			parse;
	void			*mlx;
	void			*img;
	void			*win;
	char			*screen;
	int				sizeline;
	float			ratio;
	int				cam;
}				t_global;

#endif
