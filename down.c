/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:00 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:02 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	next_char(struct s_buf *buf)
{
	ssize_t	rsize;

	if (buf->index == buf->len)
	{
		rsize = read(buf->fd, buf->buf, 4096);
		if (rsize < 0)
			panic_with_error(NULL, "fail to read because");
		buf->len = rsize;
		buf->index = 0;
	}
	if (buf->len)
		return (buf->buf[buf->index++]);
	else
		return (0);
}

void	next_token(struct s_parse *parse)
{
	while (!parse->current || parse->current == ' ' || parse->current == '\t')
	{
		parse->current = next_char(&parse->buf);
		if (parse->current == 0)
			panic_with_error(NULL, "unexpected EOF\n");
	}
}

void	eat(struct s_parse *parse, char c)
{
	if (parse->current == c)
		parse->current = next_char(&parse->buf);
	else
		panic_with_error(NULL, "unexpected token");
}
