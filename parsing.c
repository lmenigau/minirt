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

void	parse_tri(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'r');
	if (store->ntris >= 1000)
		panic_with_error("Too many triangles");
	store->tris[store->ntris].p1 = parse_vec(parse);
	store->tris[store->ntris].p2 = parse_vec(parse);
	store->tris[store->ntris].p3 = parse_vec(parse);
	store->tris[store->ntris].color = parse_vec(parse);
	store->ntris++;
}

void	parse_cyl(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->ncyls >= 1000)
		panic_with_error("Too many cylinders");
	store->cyls[store->ncyls].coord = parse_vec(parse);
	store->cyls[store->ncyls].ori = parse_vec(parse);
	store->cyls[store->ncyls].diam = parse_num(parse);
	store->cyls[store->ncyls].height = parse_num(parse);
	store->cyls[store->ncyls].color = parse_vec(parse);
	store->ncyls++;
}

void	parse_box(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->nboxs >= 1000)
		panic_with_error("Too many boxes");
	store->boxs[store->nboxs].coord = parse_vec(parse);
	store->boxs[store->nboxs].ori = parse_vec(parse);
	store->boxs[store->nboxs].size = parse_num(parse);
	store->boxs[store->nboxs].color = parse_vec(parse);
	store->nboxs++;
}

void	parse_plane(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'l');
	if (store->nplanes >= 1000)
		panic_with_error("Too many planes");
	store->planes[store->nplanes].coord = parse_vec(parse);
	store->planes[store->nplanes].ori = parse_vec(parse);
	store->planes[store->nplanes].color = parse_vec(parse);
	store->nplanes++;
}

void	parse_spherebox(struct s_parse *parse)
{
	t_store		*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'q')
		return (parse_box(parse));
	eat(parse, 'p');
	if (store->nspheres >= 1000)
		panic_with_error("Too many spheres");
	store->spheres[store->nspheres].coord = parse_vec(parse);
	store->spheres[store->nspheres].size = parse_num(parse);
	store->spheres[store->nspheres].color = parse_vec(parse);
	store->nspheres++;
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
	else if (parse->current == 'l')
		parse_light(parse);
	else if (parse->current == 's')
		parse_spherebox(parse);
	else if (parse->current == 'p')
		parse_plane(parse);
	else if (parse->current == 't')
		parse_tri(parse);
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
