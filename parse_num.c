/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:51:24 by lomeniga          #+#    #+#             */
/*   Updated: 2022/10/21 11:51:24 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

float	parse_num_cont(double pow, double nb, struct s_parse *parse)
{
	while (ft_isdigit(parse->current))
	{
		pow *= .1;
		nb += pow * (parse->current - '0');
		parse->current = next_char(&parse->buf);
	}
	return (nb);
}

float	parse_num(struct s_parse *parse)
{
	double	nb;
	double	pow;

	nb = 0;
	pow = 1;
	next_token(parse);
	if (!ft_isdigit(parse->current) && parse->current != '-')
		panic_with_error(NULL, "expecting number");
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
	return (parse_num_cont(pow, nb, parse));
}
