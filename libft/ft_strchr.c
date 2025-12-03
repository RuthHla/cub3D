/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:55:14 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 20:07:26 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return ((char *)0);
}
/*
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	char *str = argv[1];
	char c = argv[2][0];

	if (strchr(str,c) == NULL)
		printf("strchr : NULL\n");
	else
		printf("strchr : %s\n", strchr(str, c));
	if (ft_strchr(str, c) == NULL)
		printf("ft_strchr : NULL\n");
	else
		printf("ft_strchr : %s\n", ft_strchr(str, c));
}
*/
