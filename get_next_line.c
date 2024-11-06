/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:04:50 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/06 16:13:19 by edetoh           ###   ########.fr       */
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
				return (line_len);
			}
			k++;
			line_len++;
		}
		list = list->next;
	}
	return (0);
}

static char	*get_line(t_list *list)
{
	char	*line;
	int		line_len;
	int		k;
	int		i;

	if (!list)
		return (NULL);
	i = 0;
	line_len = count_len(list);
	line = malloc(line_len + 1);
	while (list)
	{
		k = 0;
		while (list->content[k] != '\0')
		{
			if (list->content[k] != '\n')
				line[i] = list->content[k];
			i++;
			k++;
		}
		list = list->next;
	}
	line[line_len + 1] = '\0';
	return (line);
}

static int	found_newline(t_list *list)
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

static void	create_list(t_list **list, int fd)
{
	int			char_read;
	char		*buffer;

	while (!found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (!char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_lstadd_back(list, ft_lstnew(buffer));
	}
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
	ft_lstclear(&list);
	return (next_line);
}

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd = open("bonjour.txt", O_RDWR | O_CREAT);
// 	char *chargnl;
// 	chargnl = get_next_line(fd);
// 	printf("=== GNL ===\n%s\n===========", chargnl);
// 	free(chargnl);
// 	return 0;
// }
