/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:03:28 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/12 17:14:53 by lomeniga         ###   ########.fr       */
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

struct	s_scene
{
	_Bool	isreso;
	_Bool	isambiant;
	t_ivec	reso;
	float	ambiant_r;
	t_vec3	ambiant;
};

struct s_buf
{		
	size_t	index;
	size_t	len;
	int		fd;
	char	buf[4096];
};

struct	s_parse
{
	struct s_buf	buf;
	struct s_scene	scene;
	char			current;
};

#endif
