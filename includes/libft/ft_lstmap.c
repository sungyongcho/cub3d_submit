/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:11:48 by sucho             #+#    #+#             */
/*   Updated: 2020/04/27 15:26:12 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *temp;
	t_list *current;

	if (lst == 0 || !(new = ft_lstnew(f(lst->content))))
		return (NULL);
	current = new;
	temp = lst->next;
	while (temp)
	{
		if (!(current->next = ft_lstnew(f(temp->content))))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		current = current->next;
		temp = temp->next;
	}
	return (new);
}
