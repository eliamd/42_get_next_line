/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:18:06 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/08 16:59:32 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	create_and_add_nodeback(t_list **lst, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->content[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

char	*ft_strdup(const char *s)
{
	char	*strduped;
	int		i;
	int		length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	strduped = malloc((length + 1) * sizeof(char));
	if (!strduped)
		return (NULL);
	i = 0;
	while (i < length)
	{
		strduped[i] = s[i];
		i++;
	}
	strduped[i] = '\0';
	return (strduped);
}

void	create_list(t_list **list, int fd)
{
	int				char_read;
	char			*buffer;

	while (!found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		create_and_add_nodeback(list, buffer);
	}
}
