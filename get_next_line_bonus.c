/* ************************************************************************** */
/*																			*/
/*													    :::      ::::::::   */
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

static void	shift_and_nullpad_buffer(char *buffer, size_t i)
{
	// size_t len;

	// len = 0;
	// while (buffer[len] && len <= BUFFER_SIZE)
	// 	len++;
	ft_memmove((void *)buffer, (void *)(buffer + i + 1), BUFFER_SIZE - i);
	while (i)
	{
		buffer[(BUFFER_SIZE - 1) - i] = '\0';
		i--;
	}
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
		ft_lstadd_back(list, ft_lstnew((void *)line, -1));
		shift_and_nullpad_buffer(buffer, i);
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
	if (!list)
		return (NULL);
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
	ft_lstclear(&list, &free);
	return (result);
}

char	*get_next_line(int fd)
{
	static t_list		*fd_buf;
	t_list				*current;
	t_list				*list;
	char				*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = fd_buf;
	while (current && current->fd != fd)
		current = current->next;
	if (!current)
	{
		buffer = malloc(BUFFER_SIZE * sizeof(char));
		shift_and_nullpad_buffer(buffer, BUFFER_SIZE - 1);
		current = ft_lstnew(buffer, fd);
	}
	current->next = fd_buf;
	fd_buf = current;
	list = NULL;
	get_next_buffer(&list, current->content, current->fd);
	return (concat_list(list));
}
