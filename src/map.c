/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:03:46 by tpolonen          #+#    #+#             */
/*   Updated: 2022/05/03 19:10:30 by teppo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**free_map(int ***map, int **col_arr, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free((*map)[i++]);
	ft_memdel((void **)map);
	ft_memdel((void **)col_arr);
	return (NULL);
}	

static void	coord_to_point(t_point2 *p, t_point3 *c, t_param *params)
{
	params->projs[params->cur_proj](p, c);
	p->x *= params->scale;
	p->y *= params->scale;
	p->x += params->margin.x;
	p->y += params->margin.y;
}

static void	get_coord(t_param *params, t_point3 *coord, int x, int z)
{
	coord->x = x;
	coord->y = params->map[z][x] * params->magnitude;
	coord->z = z;
}

void	render_map(t_param *params, t_image *buf)
{
	t_point2 cur;
	t_point2 next_x;
	t_point2 next_z;
	t_point3 coord;

	for (int z = 0; z < params->map_height; z++) {
		for (int x = 0; x < params->cols[z]; x++) {
			get_coord(params, &coord, x, z);
			coord_to_point(&cur, &coord, params);
			if (z < params->map_height - 1)
			{
				get_coord(params, &coord, x, z + 1);
				coord_to_point(&next_z, &coord, params);
				dda_draw_line(buf, &cur, &next_z, params->color);
			}
			if (x < params->cols[z] - 1)
			{
				get_coord(params, &coord, x + 1, z);
				coord_to_point(&next_x, &coord, params);
				dda_draw_line(buf, &cur, &next_x, params->color);
			}
		}
	}
}
