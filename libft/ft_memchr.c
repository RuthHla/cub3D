/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:51:07 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 18:43:14 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int c, size_t size)
{
	unsigned char	*mem_block;
	size_t			i;

	mem_block = (unsigned char *)mem;
	i = 0;
	while (i < size)
	{
		if (*mem_block == (unsigned char)c)
			return (mem_block);
		mem_block++;
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main()
{
	char test[15] = "Bonjour a tous";
	char *found;
	char c = 't';
	size_t size = 13;
	printf("Avant : %s\n", test);
	found = ft_memchr(test, c, size);
	printf("Après : %s\n", found);
}
*/
