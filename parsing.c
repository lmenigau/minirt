#include "minirt.h"

t_vec3	parse_vec(struct s_parse *parse)
{
	t_vec3		vec;

	vec.x = parse_num(parse);
	eat(parse, ',');
	vec.y = parse_num(parse);
	eat(parse, ',');
	vec.z = parse_num(parse);
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

void	print_vec(t_vec3 vec)
{
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
}
void	parse_ambiant(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (!parse->scene.isambiant)
	{
		parse->scene.ambiant_r = parse_num(parse);
		parse->scene.ambiant = parse_vec(parse);
		parse->scene.isambiant = 1;
		print_vec(parse->scene.ambiant);
	}
	else
		panic_with_error("multiple ambiant");
}

void	parse_cyl(struct s_parse *parse)
{
	parse_vec(parse);
}

void	parse_light(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->nlights >= 1000)
		panic_with_error("Too many lights");
	store->lights[store->nlights].coord = parse_vec(parse);
	store->lights[store->nlights].color = parse_vec(parse);
	store->lights[store->nlights].bright = parse_num(parse);
	store->nlights++;
}

void 	parse_camcyl(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->ncams >= 1000)
		panic_with_error("Too many cameras");
	store->cams[store->ncams].coord = parse_vec(parse);
	store->cams[store->ncams].ori = parse_vec(parse);
	store->cams[store->ncams].fov = parse_num(parse);
	store->ncams++;
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
	init_scene(&parse.scene);
	parse.buf.fd = fd;
	parse_line(&parse);
	while (parse.buf.len > 0)
	{
		parse_line(&parse);
	}
}
