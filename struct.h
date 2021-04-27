/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:03:28 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/27 15:02:41 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_options
{
	_Bool	save;
}			t_options;

typedef unsigned char	t_uchar;

typedef struct s_ivec
{
	int		x;
	int		y;
}				t_ivec;

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct s_color
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;
}				t_color;

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
	float	diam;
	float	height;
}				t_cyl;

typedef struct s_cam
{
	t_vec3	coord;
	t_vec3	ori;
	float	fov;
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
	_Bool	isreso;
	_Bool	isambiant;
	t_ivec	reso;
	float	ambiant_r;
	t_vec3	ambiant;
	t_store	st;
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
	t_options	options;
	t_parse		parse;
	void		*mlx;
	t_color		*screen;
	int			cam;
}				t_global;

#endif
