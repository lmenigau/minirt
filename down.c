#include "minirt.h"

char	next_char(struct s_buf *buf)
{
	if (buf->index == buf->len)
	{
		ssize_t (rsize) = read(buf->fd, buf->buf, 4096);
		if (rsize < 0)
			panic_with_error("read fail\n");
		buf->len = rsize;
		buf->index = 0;
	}
	if (buf->len)
		return (buf->buf[buf->index++]);
	else
		return (0);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	next_token(struct s_parse *parse)
{
	while (!parse->current || parse->current == ' ' || parse->current == '\t')
	{
		parse->current = next_char(&parse->buf);
		if (parse->current == 0)
			panic_with_error("unexcpected EOF\n");
	}
}

float	parse_num(struct s_parse *parse)
{
	double	 	nb;
	double		pow;

	nb = 0;
	pow = 1;
	next_token(parse);
	if (!ft_isdigit(parse->current) && parse->current != '-')
		panic_with_error("expecting number");
	if (parse->current == '-')
		pow = -1;
	if (parse->current == '-')
		parse->current = next_char(&parse->buf);
	while (ft_isdigit(parse->current))
	{
		nb = nb * 10 + pow * (parse->current - '0');
		parse->current = next_char(&parse->buf);
	}
	if (parse->current == '.')
		parse->current = next_char(&parse->buf);
	while (ft_isdigit(parse->current))
	{
		nb += (pow *= .1) * (parse->current - '0');
		parse->current = next_char(&parse->buf);
	}
	return (nb);
}

void	eat(struct s_parse *parse, char c)
{
	if (parse->current == c)
		parse->current = next_char(&parse->buf);
	else
		panic_with_error("unexpected token");
}
