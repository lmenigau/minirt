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
	float	 	nb;
	float		pow;

	nb = 0;
	pow = 0.1;
	next_token(parse);
	if (!ft_isdigit(parse->current))
		panic_with_error("expecting digit");
	while (ft_isdigit(parse->current))
	{
		nb = nb * 10 + (parse->current - '0');
		parse->current = next_char(&parse->buf);
	}
	if (parse->current == '.')
		parse->current = next_char(&parse->buf);
	while (ft_isdigit(parse->current))
	{
		nb += pow * (parse->current - '0');
		pow *= 0.1;
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

float parse_float(struct s_parse *parse)
{
	return (parse_num(parse));
}

t_vec3		parse_vec(struct s_parse *parse)
{
	t_vec3		vec;
	vec.x = parse_float(parse);
	eat(parse, ',');
	vec.y = parse_float(parse);
	eat(parse, ',');
	vec.z = parse_float(parse);
	return (vec);
}

void	parse_tr(void)
{
}

void	parse_res(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (!parse->scene.isreso)
	{
		parse->scene.reso.x = parse_num(parse);
		parse->scene.reso.y = parse_num(parse);
		parse->scene.isreso = 1;
	}
	else
		panic_with_error("multiple resolution");
}

void	parse_ambiant(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);

	if (!parse->scene.isambiant)
	{
		parse->scene.ambiant_r = parse_float(parse);
		parse->scene.ambiant = parse_vec(parse); 
		parse->scene.isambiant = 1;
	}
	else
		panic_with_error("multiple ambiant");
}

void	parse_cyl(struct s_parse *parse)
{
}

void 	parse_camcyl(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
}

void	parse_object(struct s_parse *parse)
{
	if (parse->current == 'R')
		parse_res(parse);
	else if (parse->current == 'A')
		parse_ambiant(parse);
	else if (parse->current == 'c')
		parse_camcyl(parse);
	else
	{
		panic_with_error("undefined object");
	}
}

void	parse_line(struct s_parse *parse)
{
	next_token(parse);
	parse_object(parse);
	next_token(parse);
	eat(parse, '\n');
}

void	parse_scene(int fd)
{
	struct s_parse (parse) = {};
	parse.buf.fd = fd;
	parse_line(&parse);
	while (parse.buf.len > 0)
	{
		parse_line(&parse);
	}
}
