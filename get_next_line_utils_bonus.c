/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 00:29:24 by cyril             #+#    #+#             */
/*   Updated: 2024/01/03 11:36:00 by cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst && new)
	{
		if (*lst)
		{
			current = *lst;
			while (current && current->next)
				current = current->next;
			current->next = new;
		}
		else
			*lst = new;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst)
	{
		while (*lst)
		{
			next = (*lst)->next;
			del((void *)((*lst)->content));
			free(*lst);
			*lst = next;
		}
		*lst = NULL;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*ptr;
	size_t				n_bytes;

	if (size && count > (size_t) - 1 / size)
		return (NULL);
	n_bytes = count * size;
	ptr = malloc(n_bytes);
	if (!ptr)
		return (NULL);
	while (n_bytes--)
		*ptr++ = 0;
	ptr -= count * size;
	return (ptr);
}

char	*ft_strndup(const char *src, size_t size)
{
	char	*ptr;
	size_t	len;

	len = 0;
	while (len < size && src[len])
		len ++;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (*src && size--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (ptr - len);
}
