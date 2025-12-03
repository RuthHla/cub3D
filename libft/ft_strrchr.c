/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:58:40 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 20:08:34 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;

	last = ((const char *)0);
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			last = str;
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return ((char *)last);
}
/*
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	char *str = argv[1];
	char c = argv[2][0];

	if (strrchr(str,c) == NULL)
		printf("strrchr : NULL\n");
	else
		printf("strrchr : %s\n", strrchr(str, c));
	if (ft_strrchr(str, c) == NULL)
		printf("ft_strrchr : NULL\n");
	else
		printf("ft_strrchr : %s\n", ft_strrchr(str, c));
}
*/
