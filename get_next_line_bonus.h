/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 03:40:47 by cyril             #+#    #+#             */
/*   Updated: 2023/12/24 08:38:16 by cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int 			fd;
	void			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_memmove(void *dest, const void *src, size_t n);
t_list	*ft_lstnew(void *content, int fd);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	*ft_strndup(const char *src, size_t size);

#endif