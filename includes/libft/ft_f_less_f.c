/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_less_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:35:12 by jmehlig           #+#    #+#             */
/*   Updated: 2022/10/23 14:49:16 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_f_less_f(float f1, float f2)
{
	float	precision;

	precision = 0.00001;
	if (((f1 + precision) < f2))
		return (1);
	else
		return (0);
}
