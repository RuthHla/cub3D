/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:02:55 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:05:20 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		join[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	join[len] = '\0';
	return (join);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	(void) argc;
	char *s1 = argv[1];
	char *s2 =  argv[2];
	printf("%s\n", ft_strjoin(s1, s2));
}
*/
