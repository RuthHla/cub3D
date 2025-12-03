/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:56:44 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:17:45 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && (i < len - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	(void) argc;
	char *s1 = argv[1];
	char *s2 = argv[2];
	int len = atoi(argv[3]);

	printf("ft_strncmp : %i\n", ft_strncmp(s1, s2, len));
	printf("strncmp : %i\n", strncmp(s1, s2, len));
}
*/
