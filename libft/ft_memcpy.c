/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:53:33 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:07:15 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < size)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
int main()
{
	int array[] = {54, 85, 20, 63, 21};
	int *copy = NULL;
	int length = sizeof(int) * 5;

	copy = (int *) malloc(length);
	ft_memcpy(copy, array, length);
	int i = 0;
	while (i < 5)
		printf("%i, ", copy[i++]);
	printf("\n");
}
*/
