#include "header.h"

t_obj_struct	*get_next_elem(t_obj_struct *start, char id)
{
	/*
	   iterate until current element is found
	   then iterate until the next element with id is found
	   return NULL if not found
	 */
	if (!start)
		return (start);
	start = start->next;
	while (start)
	{
		if (start->id == id)
			return (start);
		start = start->next;
	}
	return (start);
}

int		main(void)
{
	/*
	  generate scene struct
	  use parser to fill with scene information
	  loop through obj structs and for each camera found, call ray tracer
	  also need to generate a new image for each camera found
	  ray tracer needs to be passed scene struct, camera struct and image address*/
	
	char			first;
	char			*file;
	void			*img_addr;
	t_scene_struct	s;
	t_win_struct	ws;
	t_obj_struct	*cam;

	file = "file.rt";
	//init_win_struct(&ws);
	s.obj_list = NULL;
	s.viewport_distance = 1;
	parser(&s, file);

	/*
	  set up window and create image for ray tracing
	*/

	ws.res_x = s.res_xy[X];
	ws.res_y = s.res_xy[Y];
	//initialise_window(&ws);

	first = 0;
	cam = s.obj_list;
	if (cam->id == 'C')
		first = 1;
	while(first == 1 || (cam = get_next_elem(cam, 'C')))
	{
		print_elem(cam);
		printf("\n\n");
		//img_ptr = mlx_new_image(ws.mlx_ptr, ws.res_x, ws.res_y);
		//img_addr = mlx_get_data_addr(ws.img_ptr, &bpp, &line_size, &endian);
		//trace_rays(&s, cam, img_addr);
		/*add new image to list of images in win_struct*/
		/*currently only one camera so just point ws.img_ptr to img_ptr*/
		//ws.img_ptr = img_ptr;
		first = 0;
	}
	
	//mlx_loop(ws.mlx_ptr);
	/*free stuff*/
}
