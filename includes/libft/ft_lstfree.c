/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:12:07 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 18:12:07 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*temp;

	while ((*lst)->content != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelnode(lst, temp->content);
	}
}
