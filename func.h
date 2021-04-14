/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:22:41 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/14 13:43:00 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "minirt.h"

void	next_token(struct s_parse *parse);
char	next_char(struct s_buf *buf);
void	eat(struct s_parse *parse, char c);
float	parse_num(struct s_parse *parse);
void	parse_scene(int fd);
void	panic_with_error(char *str);
void	print(const char *str);
void	init_scene(struct s_scene *scene);

void	parse_tr(void);
void	parse_res(struct s_parse *parse);
void	parse_ambiant(struct s_parse *parse);
void	parse_cyl(struct s_parse *parse);
void	parse_light(struct s_parse *parse);
void	parse_camcyl(struct s_parse *parse);

#endif
