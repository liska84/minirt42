/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:26:08 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/29 14:37:28 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


// gehe durch c, splitte einzeln danach
// dann gehe durch die gesplitteten 
// (A) (0.2         255,255,255) -> (A)() ((0.2), (255, 255, 255))


static int  ft_strlen_double(char **s)
{
    int i;

    i = 0;
    if (s == NULL)
        return (0);
    while (s[i] != NULL)
    {
        i++;
    }
    return (i);
}

static char **ft_strjoin_ptr(char **s1, char **s2)
{
   	char	**ptr;
	int	lens1;
	int	lens2;
	int	i;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen_double(s1);
	lens2 = ft_strlen_double(s2);
	i = -1;
	ptr = (char **)malloc(sizeof(char*) * (lens1 + lens2 + 1));
	if (!ptr)
		return (0);
	while (++i < lens1)
		ptr[i] = ft_strdup(s1[i]);
	while (i < lens1 + lens2)
	{
		ptr[i] = ft_strdup(s2[i - lens1]);
		i++;
	}
	ptr[i] = 0;
	//ft_split_del(&s1);
    //ft_split_del(&s2);
	return (ptr);
}


char **ft_split_multi(const char *str, char *c)
{
    char **res;
    char **tmp;
    char **add;
    int j;
    int i;

    res = ft_split(str, c[0]);
    add = malloc(sizeof(char(*)) * 2);
    *add = "\0";
    add[1] = NULL;
    if (res == NULL || c[0] == '\0')
        return (NULL);
    i = 1;
    while (c[i] != '\0')
    {
        j = 0;
        while (res[j])
        {
            tmp = ft_split(res[j], c[i]);
            add = ft_strjoin_ptr(add, tmp);
            j++;
        }
        ft_split_del(&res);
        res = add;
        //ft_split_del(&add);
        i++;
    }
    return (res);
}
