#include "minirt.h"

void	init_scene_cont(struct s_scene *scene)
{
	static t_box	boxs[1000];
	static t_cyl	cyls[1000];
	static t_tri	tris[1000];

	scene->st.boxs = boxs;
	scene->st.cyls = cyls;
	scene->st.tris = tris;
}

void	init_scene(struct s_scene *scene)
{
	static t_cam	cams[1000];
	static t_light	lights[1000];
	static t_sphere	spheres[1000];
	static t_plane	planes[1000];

	scene->st.cams = cams;
	scene->st.lights = lights;
	scene->st.spheres = spheres;
	scene->st.planes = planes;
	init_scene_cont(scene);
}

t_global	*init_global(void)
{
	static t_global	global;

	return (&global);
}
