/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 07:25:38 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/30 14:47:30 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H 
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


typedef struct	s_scene
{
	_Bool	isreso;
	_Bool	isambiant;
	t_ivec	reso;
}			t_scene;
#endif
