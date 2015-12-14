/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 16:09:24 by mbarbari          #+#    #+#             */
/*   Updated: 2015/12/13 23:49:25 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "framework_math/fk_vector.h"
# include "framework_shape/fk_objects.h"
# include "framework_collision/fk_intersect.h"

typedef struct		s_env t_env;
typedef struct		s_resolution
{
	int				height;
	int				width;
}					t_resolution;

struct				s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	t_resolution	resolution;
	int				fov;
	t_vertex3		pos_absolute_camera;
	t_vector3		dir_camera;
	t_fctinter		fctinter[DEFAULT];
};

void		ft_setup_inter(t_fctinter *inter);
#endif
