/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 00:29:24 by cyril             #+#    #+#             */
/*   Updated: 2023/12/24 02:42:17 by cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*_src;
	unsigned char	*_dest;

	_src = (unsigned char *)src;
	_dest = (unsigned char *)dest;
	if (_dest < _src || _dest >= _src + n)
	{
		while (n--)
			*_dest++ = *_src++;
	}
	else
	{
		while (n--)
			*(_dest + n) = *(_src + n);
	}
	return (dest);
}

char	*ft_strndup(const char *src, size_t size)
{
	char	*ptr;
	size_t	len;

	len = 0;
	while (src[len] && len < size)
		len ++;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (*src && size--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (ptr - len);
}
