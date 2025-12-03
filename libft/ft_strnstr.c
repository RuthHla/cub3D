/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:57:34 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 19:57:12 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while ((str[i + j] == to_find[j]) && (i + j < len))
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *) &str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *) &str[i]);
		i++;
	}
	return ((char *)0);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	(void) argc;
	size_t len = atoi(argv[3]);
	if (ft_strnstr(argv[1], argv[2], len) == NULL)
		printf("NULL");
	else
		printf("%s\n", ft_strnstr(argv[1], argv[2], len));
}
*/
