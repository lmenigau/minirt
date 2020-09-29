/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 07:25:38 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/29 10:41:08 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINIRT_H
# define MINIRT_H 

typedef struct	s_ivec;
{
	int	x;
	int y;
}				t_ivec;

typedef struct	s_options
{
	_Bool	save;
	t_ivec	reso;

}			t_options;
#endif
