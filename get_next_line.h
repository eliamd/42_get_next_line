/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:13:45 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/06 19:13:35 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int				found_newline(t_list *list);
void			polish_list(t_list **list);
void			ft_lstadd_back(t_list **lst, char *buffer);
void			dealloc(t_list **list, t_list *clean_node, char *buf);
t_list			*ft_lstlast(t_list *lst);
char			*ft_strdup(const char *s);
void			create_list(t_list **list, int fd);

char			*get_next_line(int fd);

#endif
