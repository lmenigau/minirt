/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:22:41 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/28 14:16:13 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "minirt.h"

void		next_token(struct s_parse *parse);
char		next_char(struct s_buf *buf);
void		eat(struct s_parse *parse, char c);
float		parse_num(struct s_parse *parse);
void		parse_scene(t_global *global, int fd);
void		panic_with_error(char *str);
void		print(const char *str);
void		init_scene(struct s_scene *scene);
t_global	*init_global(void);

void		parse_tr(void);
void		parse_res(struct s_parse *parse);
void		parse_ambiant(struct s_parse *parse);
void		parse_cyl(struct s_parse *parse);
void		parse_light(struct s_parse *parse);
void		parse_camcyl(struct s_parse *parse);

t_vec3		cross(t_vec3 a, t_vec3 b);
float		dot(t_vec3 v1, t_vec3 v2);
t_vec3		norm(t_vec3 vec);
float		len(t_vec3 vec);

void		screen(t_global *global);
t_color		render(t_global *global, t_ivec coord);
#endif
