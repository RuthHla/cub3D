/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:19:22 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:04:21 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*str;
	size_t	i;

	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	str = (char *)s + start;
	i = 0;
	while ((start + i < ft_strlen(s)) && (i < len))
	{
		substr[i] = str[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	const char *s = argv[1];
	int start = atoi(argv[2]);
	size_t len = atoi(argv[3]);
	printf("%s\n", ft_substr(s, start, len));
}
*/
