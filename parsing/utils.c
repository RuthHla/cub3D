/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:54 by alandel           #+#    #+#             */
/*   Updated: 2025/12/10 10:56:43 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

void	free_map_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_empty_line(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0' || s[i] == '\n');
}

int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '0' && s[i] != '1' && !is_space(s[i]) && s[i] != 'N'
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}
