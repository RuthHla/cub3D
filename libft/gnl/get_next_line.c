/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:32 by alandel           #+#    #+#             */
/*   Updated: 2025/12/09 11:38:29 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_type	*list;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_save(fd, &list);
	if (list == NULL)
		return (NULL);
	extract_line(list, &line);
	clean_list(&list);
	if (line[0] == '\0')
	{
		free_listt(list);
		list = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_save(int fd, t_type **list)
{
	char	*buffer;
	int		readed;

	readed = 1;
	while (!if_line(*list) && readed != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		readed = (int)read(fd, buffer, BUFFER_SIZE);
		if ((readed == 0 && *list == NULL) || readed == -1)
		{
			free(buffer);
			free_listt(*list);
			*list = NULL;
			return ;
		}
		buffer[readed] = '\0';
		add_to_list(list, buffer, readed);
		free(buffer);
	}
}

void	add_to_list(t_type **list, char *buffer, int readed)
{
	int		i;
	t_type	*last;
	t_type	*new_node;

	new_node = malloc(sizeof(t_type));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < readed)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	last = ft_lstlastt(*list);
	last->next = new_node;
}

void	extract_line(t_type *list, char **line)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	generate_line(line, list);
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if ((list->content[i]) == '\n')
			{
				(*line)[j++] = list->content[i++];
				break ;
			}
			(*line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
}

void	clean_list(t_type **list)
{
	t_type	*last;
	t_type	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_type));
	if (clean_node == NULL || list == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lstlastt(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content != NULL && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlenn(last->content) - i)
				+ 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_listt(*list);
	*list = clean_node;
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("f.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}*/
