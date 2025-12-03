/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:04:31 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:04:19 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_trim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	len_trim(char const *s1, char const *set)
{
	size_t	len_str;
	size_t	i;
	size_t	j;

	len_str = ft_strlen(s1);
	i = 0;
	j = len_str - 1;
	while (s1[i] && char_to_trim(s1[i], set))
		i++;
	if (i == len_str)
		return (0);
	while ((j != 0) && char_to_trim(s1[j], set))
	{
		j--;
		i++;
	}
	return (len_str - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*trimmed_str;

	len = len_trim(s1, set);
	trimmed_str = malloc(sizeof(char) * (len + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (s1[i] && char_to_trim(s1[i], set))
		i++;
	j = 0;
	while (j < len)
	{
		trimmed_str[j] = s1[i];
		i++;
		j++;
	}
	trimmed_str[len] = '\0';
	return (trimmed_str);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	char *str = argv[1];
	char *set = argv[2];
	printf("%s\n", ft_strtrim(str, set));
}
*/
