/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:14 by alandel           #+#    #+#             */
/*   Updated: 2025/12/09 11:38:32 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 1000
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_type
{
	char			*content;
	struct s_type	*next;
}					t_type;

int					ft_strlenn(char *str);
int					if_line(t_type *list);
t_type				*ft_lstlastt(t_type *list);
void				generate_line(char **line, t_type *list);
void				free_listt(t_type *list);
void				read_and_save(int fd, t_type **list);
void				add_to_list(t_type **list, char *buffer, int readed);
void				extract_line(t_type *list, char **line);
void				clean_list(t_type **list);
char				*get_next_line(int fd);

#endif
