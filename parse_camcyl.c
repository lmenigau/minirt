#include "func.h"

void	parse_matcyl(t_cyl *cyl)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scale;

	set_translation(&translation, cyl->coord);
	printf("translation\n");
	printmat4(translation);
	set_rotation(&rotation, (t_vec3){0, 0, 1}, cyl->ori);
	printf("rotation\n");
	printmat4(rotation);
	set_scale(&scale, cyl->radius, cyl->radius, cyl->height / 2);
	printf("scale\n");
	printmat4(scale);
	cyl->mat = mat4mul(translation, rotation);
	printf("translation * rotation\n");
	printmat4(cyl->mat);
	cyl->mat = mat4mul(cyl->mat, scale);
	printf("* scale\n");
	printmat4(cyl->mat);
	cyl->inv_mat = mat4inv(cyl->mat);
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
	store->cyls[store->ncyls].radius = parse_num(parse) / 2;
	store->cyls[store->ncyls].height = parse_num(parse);
	store->cyls[store->ncyls].color = parse_color(parse);
	parse_matcyl(&store->cyls[store->ncyls]);
	printf("mat\n");
	printmat4(store->cyls[store->ncyls].mat);
	printf("inv mat\n");
	printmat4(store->cyls[store->ncyls].inv_mat);
	store->ncyls++;
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
	cam->ori = parse_ori(parse);
	cam->fov = parse_num(parse) * M_PI / 180 ;
	cam->scale = tan(cam->fov / 2);
	cam->mat.f = mul(norm(cam->ori), -1);
	parse_matcam(cam);
	store->ncams++;
}

void	parse_bigc(struct s_parse *parse)
{
	if (parse->scene.iscam)
		panic_with_error(NULL, "there must be a signle C cam");
	else
		parse_cam(parse);
	parse->scene.iscam= 1;
}
