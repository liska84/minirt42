/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:27:39 by jmehlig           #+#    #+#             */
/*   Updated: 2022/10/22 21:44:10 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

float	ft_compare_float(float f1, float f2)
{
	float diff;
	float precision;

	precision = 0.000001;
	if (f1 == f2)
		return 0;
	diff = f1 - f2;
	if (diff < precision)
        return 0;
    else
        return diff;
}
