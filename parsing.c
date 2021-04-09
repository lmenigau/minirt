/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:21:12 by lomeniga          #+#    #+#             */
/*   Updated: 2021/04/09 16:10:47 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	next_char(struct s_buf *buf)
{
	if (buf->index == buf->len)
	{
		ssize_t (rsize) = read(buf->fd, buf->buf, 4096);
		if (buf->len < 0)
			panic_with_error("Error\n");
		buf->len = rsize;
		buf->index = 0;
	}
	return (buf->buf[buf->index++]);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	parse_num(struct s_parse *parse)
{
	int		nb;

	nb = 0;
	if (!ft_isdigit(parse->current))
		panic_with_error("Error\n");
	while (ft_isdigit(parse->current))
	{
		nb = nb * 10 + (parse->current - '0');
		parse->current = next_char(&parse->buf);
	}
	return (nb);
}

int	parse_vec(void)
{
	return (0);
}

int	parse_tr(void)
{
	return (0);
}

int	parse_object(void)
{
	return (0);
}

int	parse_line(void)
{
	return (0);
}

void	next_token(struct s_parse *parse)
{
	while ((parse->current && parse->current == ' ') || parse->current == '\t')
	{
		parse->current = next_char(&parse->buf);
	}
}

int	parse_res(struct s_parse *parse)
{
	if (!parse->scene.isreso)
	{
		parse->scene.reso.x = parse_num(parse);
		parse->scene.reso.y = parse_num(parse);
		parse->scene.isreso = 1;
	}
	else
	{
	}
	return (0);
}

int	parse_scene(int fd)
{
	struct s_parse (parse) = {};
	parse.buf.fd = fd;
	parse.current = next_char(&parse.buf);
	if (parse.current == 'R')
		parse_res(&parse);
	else if (parse.current == 'A')
	{
	}
	return (0);
}
