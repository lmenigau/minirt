/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:22:41 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 09:38:02 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "minirt.h"

void		hit_sphere(t_sphere sp, t_ray ray, t_hit *hit);
char		next_char(struct s_buf *buf);
float		dot(t_vec3 v1, t_vec3 v2);
float		len(t_vec3 vec);
float		parse_num(struct s_parse *parse);
float		plane_solver(t_plane pl, t_ray ray);
float		sphere_solver(t_sphere sp, t_ray ray);
int			ft_strcmp(const char *s1, const char *s2);
void		hit_plane(t_plane pl, t_ray ray, t_hit *hit);
size_t		ft_strlen(char *s);
t_color		render(t_global *global, t_ivec coord);
t_global	*init_global(void);
t_vec3		add(t_vec3 v1, t_vec3 v2);
t_vec3		clamp(t_vec3 v);
t_vec3		cross(t_vec3 a, t_vec3 b);
t_vec3		light(t_scene *scene, t_hit hit);
t_vec3		mul(t_vec3 vec, float b);
t_vec4		mul4(t_vec4 vec, double b);
t_vec3		vmul(t_vec3 v1, t_vec3 v2);
t_vec3		add(t_vec3 v1, t_vec3 v2);
t_vec3		sub(t_vec3 v1, t_vec3 v2);
t_vec4		sub4(t_vec4 v1, t_vec4 v2);
t_vec3		norm(t_vec3 vec);
t_vec3		parse_color(struct s_parse *parse);
t_vec3		parse_ori(struct s_parse *parse);
t_vec3		parse_vec(struct s_parse *parse);
t_vec3		sub(t_vec3 v1, t_vec3 v2);
t_vec3		transform(t_mat mat, t_vec3 v);
t_vec3		vmul(t_vec3 v1, t_vec3 v2);
void		eat(struct s_parse *parse, char c);
void		init_scene(struct s_scene *scene);
void		next_token(struct s_parse *parse);
void		panic_with_error(t_global *g, char *str);
void		parse_ambiant(struct s_parse *parse);
void		parse_bigc(struct s_parse *parse);
void		parse_camcyl(struct s_parse *parse);
void		parse_cam(struct s_parse *parse);
void		parse_cyl(struct s_parse *parse);
void		parse_light(struct s_parse *parse);
void		parse_plane(struct s_parse *parse);
void		parse_res(struct s_parse *parse);
void		parse_scene(t_global *global, int fd);
void		parse_spherebox(struct s_parse *parse);
void		parse_tri(struct s_parse *parse);
void		parse_tr(void);
void		print(const char *str);
void		pvec3(t_vec3 v);
void		screen(t_global *global);
void		store_pixel(t_global *global, t_ivec pos, t_color col);
void		iterate_pixels(t_global *global);
t_color		render(t_global *global, t_ivec coord);
t_vec3		light(t_scene *scene, t_hit hit);

float		plane_solver(t_plane pl, t_ray ray);
float		sphere_solver(t_sphere sp, t_ray ray);
void		hit_cyl(t_cyl cy, t_ray ray, t_hit *hit);

void		pvec3(t_vec3 v);
size_t		ft_strlen(char *s);
int			ft_strcmp(const char *s1, const char *s2);

void		set_rotation(t_mat4	*mat, t_vec3 v1, t_vec3 v2);
void		set_translation(t_mat4 *mat, t_vec3 coord);
void		set_scale(t_mat4 *mat, float x, float y, float z);
t_mat4		mat4mul(t_mat4 m1, t_mat4 m2);
void		set_identity(t_mat4 *mat);
t_mat4		mat4inv(t_mat4 m);
void		printmat4(t_mat4 m);
t_vec4		transform4(t_mat4 mat, t_vec4 v);
_Bool		is_colinear(t_vec3 v1, t_vec3 v2);
t_vec3		set_worldpoint(t_cyl cy, t_vec3 loc_v);
int			is_identity(t_mat4 m);
void		inv_col1_rows(t_mat4 *m, t_mat4 *id);
void		inv_col2_rows(t_mat4 *m, t_mat4 *id);
_Bool		cyl_inter(t_vec2 d, t_cyl cy, t_ray ray, t_hit *hit);
float		caps_solver(t_ray ray);
_Bool		cyl_inter(t_vec2 d, t_cyl cy, t_ray ray, t_hit *hit);
_Bool		caps_inter(t_vec2 d, t_cyl cy, t_ray ray, t_hit *hit);
float		cyl_solver(t_ray ray);
t_ray		set_locray(t_cyl cy, t_ray ray);

#endif
