/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 07:25:38 by lomeniga          #+#    #+#             */
/*   Updated: 2020/10/22 17:08:52 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H 

# include <stddef.h>

typedef struct	s_options
{
	_Bool	save;
}			t_options;


typedef	unsigned char	t_uchar;

typedef struct	s_ivec
{
	int	x;
	int y;
}				t_ivec;

typedef struct s_color
{
	t_uchar r;
	t_uchar g;
	t_uchar b;
}				t_color;


struct	s_scene
{
	_Bool	isreso;
	_Bool	isambiant;
	t_ivec	reso;
};

struct s_buf
{		
	size_t	index;
	int		fd;
	char	buf[4096];
};

struct	s_parse
{
	struct s_scene	scene;
	struct s_buf	buf;	
};

#endif
