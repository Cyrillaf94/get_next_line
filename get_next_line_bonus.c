/* ************************************************************************** */
/*																			*/
/*												        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:55:04 by cyril             #+#    #+#             */
/*   Updated: 2023/12/24 02:16:15 by cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdio.h>

static void	shift_buffer(char *buffer, size_t index)
{
	size_t	_index;

	_index = 0;
	while (index < (size_t)BUFFER_SIZE && buffer[index])
		buffer[_index++] = buffer[index++];
	while (_index <= index && _index < (size_t)BUFFER_SIZE)
		buffer[_index++] = '\0';
}

static void	get_next_buffer(t_list **list, char *buffer, int fd)
{
	int			i;
	char		c;
	char		*line;
	ssize_t		read_size;

	i = 0;
	while (buffer[i] && buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	c = buffer[i];
	if (c == '\n' || i > 0)
	{
		line = ft_strndup(buffer, i + 1);
		if (!line)
			return (ft_lstclear(list, &free));
		ft_lstadd_back(list, ft_lstnew((void *)line));
		shift_buffer(buffer, i + 1);
	}
	if (c != '\n')
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (ft_lstclear(list, &free));
		if (read_size > 0)
			get_next_buffer(list, buffer, fd);
	}
}

void	fill_concat_str(char *str, t_list *list)
{
	char	*temp;

	while (list != NULL)
	{
		temp = (char *)list->content;
		while (*temp)
			*str++ = *temp++;
		list = list->next;
	}
	*str = '\0';
}

static char	*concat_list(t_list *list)
{
	int		total_length;
	t_list	*current;
	char	*str;
	char	*result;

	total_length = 0;
	current = list;
	while (current != NULL)
	{
		str = (char *)current->content;
		while (*str++)
			total_length++;
		current = current->next;
	}
	result = malloc(total_length + 1);
	if (result == NULL)
		return (NULL);
	fill_concat_str(result, list);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	t_list		*list;
	char		*result;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	get_next_buffer(&list, buffer[fd], fd);
	if (list == NULL)
		return (NULL);
	result = concat_list(list);
	ft_lstclear(&list, &free);
	return (result);
}
