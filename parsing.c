#include "minirt.h"
#include "struct.h"
#include <math.h>

t_vec3	parse_vec(struct s_parse *parse)
{
	t_vec3	vec;

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
		panic_with_error(NULL, "multiple resolution");
}

_Bool	in_range(t_vec3 v, float low, float high)
{
	if (v.x < low || v.x > high)
		return (0);
	else if (v.y < low || v.y > high)
		return (0);
	else if (v.z < low || v.z > high)
		return (0);
	return (1);
}

t_vec3	parse_color(struct s_parse *parse)
{
	t_vec3	c;

	c = parse_vec(parse);
	if (!in_range(c, 0, 255))
		panic_with_error(NULL, "color out of bound");
	return ((t_vec3){c.x / 255, c.y / 255, c.z / 255});
}

void	parse_ambiant(struct s_parse *parse)
{
	parse->current = next_char(&parse->buf);
	if (!parse->scene.isambiant)
	{
		parse->scene.ambiant_r = parse_num(parse);
		parse->scene.ambiant = mul(parse_color(parse), parse->scene.ambiant_r);
		parse->scene.isambiant = 1;
	}
	else
		panic_with_error(NULL, "multiple ambiant");
}

void	parse_tri(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'r');
	if (store->ntris >= 1000)
		panic_with_error(NULL, "Too many triangles");
	store->tris[store->ntris].p1 = parse_vec(parse);
	store->tris[store->ntris].p2 = parse_vec(parse);
	store->tris[store->ntris].p3 = parse_vec(parse);
	store->tris[store->ntris].color = parse_color(parse);
	store->ntris++;
}

void	parse_cyl(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->ncyls >= 1000)
		panic_with_error(NULL, "Too many cylinders");
	store->cyls[store->ncyls].coord = parse_vec(parse);
	store->cyls[store->ncyls].ori = parse_vec(parse);
	store->cyls[store->ncyls].diam = parse_num(parse);
	store->cyls[store->ncyls].height = parse_num(parse);
	store->cyls[store->ncyls].color = parse_color(parse);
	store->ncyls++;
}

void	parse_box(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (store->nboxs >= 1000)
		panic_with_error(NULL, "Too many boxes");
	store->boxs[store->nboxs].coord = parse_vec(parse);
	store->boxs[store->nboxs].ori = parse_vec(parse);
	store->boxs[store->nboxs].size = parse_num(parse);
	store->boxs[store->nboxs].color = parse_color(parse);
	store->nboxs++;
}

void	parse_plane(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	eat(parse, 'l');
	if (store->nplanes >= 1000)
		panic_with_error(NULL, "Too many planes");
	store->planes[store->nplanes].coord = parse_vec(parse);
	store->planes[store->nplanes].ori = parse_vec(parse);
	store->planes[store->nplanes].color = parse_color(parse);
	store->nplanes++;
}

void	parse_spherebox(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'q')
		return (parse_box(parse));
	eat(parse, 'p');
	if (store->nspheres >= 1000)
		panic_with_error(NULL, "Too many spheres");
	store->spheres[store->nspheres].coord = parse_vec(parse);
	store->spheres[store->nspheres].size = parse_num(parse) / 2;
	store->spheres[store->nspheres].color = parse_color(parse);
	store->nspheres++;
}

void	parse_light(struct s_parse *parse)
{
	t_store	*store;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->nlights >= 1000)
		panic_with_error(NULL, "Too many lights");
	store->lights[store->nlights].coord = parse_vec(parse);
	store->lights[store->nlights].bright = parse_num(parse);
	store->lights[store->nlights].color = parse_color(parse);
	store->nlights++;
}

void	parse_matcam(t_cam *cam)
{
	cam->mat.f = mul(norm(cam->ori), -1);
	if (cam->mat.f.x == 0 && cam->mat.f.z == 0)
	{
		cam->mat.u = norm(cross((t_vec3){1, 0, 0}, cam->mat.f));
		cam->mat.r = cross(cam->mat.f, cam->mat.u);
	}
	else
	{
		cam->mat.r = norm(cross((t_vec3){0, -1, 0}, cam->mat.f));
		cam->mat.u = cross(cam->mat.r, cam->mat.f);
	}
}

void	parse_cam(struct s_parse *parse)
{
	t_store	*store;
	t_cam	*cam;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->ncams >= 1000)
		panic_with_error(NULL, "Too many cameras");
	cam = &store->cams[store->ncams];
	cam->coord = parse_vec(parse);
	cam->ori = parse_vec(parse);
	cam->fov = parse_num(parse) * M_PI / 180 ;
	cam->scale = tan(cam->fov / 2);
	cam->mat.f = mul(norm(cam->ori), -1);
	parse_matcam(cam);
	store->ncams++;
}

void	parse_camcyl(struct s_parse *parse)
{
	t_store	*store;
	t_cam	*cam;

	store = &parse->scene.st;
	parse->current = next_char(&parse->buf);
	if (parse->current == 'y')
		return (parse_cyl(parse));
	if (store->ncams >= 1000)
		panic_with_error(NULL, "Too many cameras");
	cam = &store->cams[store->ncams];
	cam->coord = parse_vec(parse);
	cam->ori = parse_vec(parse);
	cam->fov = parse_num(parse) * M_PI / 180;
	cam->scale = tan(cam->fov / 2);
	cam->mat.f = norm(cam->ori);
	cam->mat.r = cross((t_vec3){0, 1, 0}, cam->mat.f);
	cam->mat.u = cross(cam->mat.f, cam->mat.r);
	store->ncams++;
}

void	parse_object(struct s_parse *parse)
{
	if (parse->current == 'R')
		parse_res(parse);
	else if (parse->current == 'A')
		parse_ambiant(parse);
	else if (parse->current == 'C')
		parse_cam(parse);
	else if (parse->current == 'c')
		parse_camcyl(parse);
	else if (parse->current == 'L')
		parse_light(parse);
	else if (parse->current == 's')
		parse_spherebox(parse);
	else if (parse->current == 'p')
		parse_plane(parse);
	else if (parse->current == 't')
		parse_tri(parse);
	else if (parse->current == '\n')
		;
	else
		panic_with_error(NULL, "undefined object");
}

void	parse_line(struct s_parse *parse)
{
	next_token(parse);
	parse_object(parse);
	next_token(parse);
	eat(parse, '\n');
}

void	parse_scene(t_global *global, int fd)
{
	init_scene(&global->parse.scene);
	global->parse.buf.fd = fd;
	parse_line(&global->parse);
	while (global->parse.buf.len > 0)
	{
		parse_line(&global->parse);
	}
}
