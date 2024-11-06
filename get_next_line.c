/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:04:50 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/06 19:17:53 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	count_len(t_list *list)
{
	int		line_len;
	int		k;

	line_len = 0;
	while (list)
	{
		k = 0;
		while (list->content[k] != '\0')
		{
			if (list->content[k] == '\n')
			{
				line_len++;
				return (line_len);
			}
			k++;
			line_len++;
		}
		list = list->next;
	}
	return (line_len);
}

static char	*get_line(t_list *list)
{
	char	*line;
	int		line_len;
	int		k;
	int		i;

	k = 0;
	line_len = count_len(list);
	line = malloc((line_len + 1) * sizeof(char));
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				line[k++] = '\n';
				line[k] = '\0';
				return (line);
			}
			line[k++] = list->content[i++];
		}
		list = list->next;
	}
	line[k] = '\0';
	return (line);
}

int	found_newline(t_list *list)
{
	char	*last_content_string;
	int		i;

	if (!list)
		return (0);
	last_content_string = ft_lstlast(list)->content;
	i = 0;
	while (last_content_string[i] != '\0')
	{
		if (last_content_string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd = open("bonjour.txt", O_RDONLY);
// 	int line = 1;
// 	char *chargnl;

// 	while ((chargnl = get_next_line(fd)))
// 		printf("%d -> %s\n", line++, chargnl);
// 	free(chargnl);
// 	return 0;
// }
