/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:21:36 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:05:15 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	res;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	res = 0;
	if (size <= dst_len)
		res = size + src_len;
	else
		res = dst_len + src_len;
	i = 0;
	while (src[i] && (dst_len + i + 1 < size))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (res);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	(void) argc;
	char *dest_test = argv[1];
	char *src_test = argv[2];
	size_t	stest = atoi(argv[3]);

	char real_dest[100];
	char real_src[100];
	strcpy(real_dest, dest_test);
	strcpy(real_src, src_test);

	printf("strlcat : %li\n", strlcat(dest_test, src_test, stest));
	printf("ft_strlcat : %li\n", ft_strlcat(real_dest, real_src, stest));
}
*/
