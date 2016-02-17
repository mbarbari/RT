/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 18:30:44 by mbarbari          #+#    #+#             */
/*   Updated: 2016/02/15 16:17:03 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framework_light/fk_light.h"
#include "framework_shape/fk_type.h"
#include "framework_math/fk_vector.h"
#include <stdlib.h>

static t_color3	lambert_low(t_intersect inter, t_spotlight light, t_color3 ptcolor)
{
	float		angle;
	t_vector3	v_light;

	v_light = vector_unit(vector_substract(inter.pos, light.pos));
	angle = vector_dotproduct(vector_unit(v_light), vector_unit(inter.v_normal));
	return (vector_div(vector_mul(vector_sum(ptcolor, vector_mul(light.color, angle)), light.intensity), 2));
}

static t_color3	light_low(t_intersect inter, t_spotlight light, t_color3 ptcolor)
{
	float		angle;
	float		diff;
	t_vector3	v_light;
	t_color3	color;

	v_light = vector_unit(vector_substract(light.pos, inter.pos));
	angle = vector_dotproduct(inter.v_normal, v_light);
	if (inter.obj->diffuse > 0)
		if (angle > 0)
		{
			diff = angle * inter.obj->diffuse;
			color = vector_sum(ptcolor, vector_mul(vector_product(ptcolor, light.color), diff));
			return color;
		}
	return ptcolor;
}

static t_color3	specular_low(t_intersect inter, t_spotlight light, t_color3 ptcolor)
{
	t_vector3	v;
	t_vector3	r;
	t_color3	color;
	float		angle;
	float		spec;

	v = inter.ray.dir;
	r = vector_substract(vector_substract(light.pos, inter.pos), vector_mul(inter.v_normal, (2.0f * vector_dotproduct(vector_substract(light.pos, inter.pos), inter.v_normal))));
	angle = vector_dotproduct(v, r);
	if (angle > 0)
	{
		//angle = vector_dotproduct(inter.v_normal, r) / compute_len(r.x, r.y, r.x);
		spec = powf(angle, 20) * 0.8;
		color = vector_sum(ptcolor, vector_mul(light.color, spec));
		//color = vector_sum(ptcolor, vector_mul(vector_product(ptcolor, light.color), spec));
		return color;
	}
	return color_new(0.0,0.0,0.0);
}

t_color3			iter_light(t_intersect inter, t_spotlight *light)
{
	//return (specular_low(inter, *light, lambert_low(inter, *light, ((t_object *)inter.obj)->color)));
	//return (specular_low(inter, *light, ((t_object *)inter.obj)->color));
	//return (lambert_low(inter, *light, ((t_object *)inter.obj)->color));
	return (vector_div(vector_sum(specular_low(inter, *light, ((t_object *)inter.obj)->color), lambert_low(inter, *light, ((t_object *)inter.obj)->color)), 2));
}
