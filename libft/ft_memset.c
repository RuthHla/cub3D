/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:28 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:06:50 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = s;
	while (i < n)
	{
		*dest = (unsigned char) c;
		i++;
		dest++;
	}
	return (s);
}
/*
#include <stdio.h>
int main()
{
	int array[] = {54, 85, 20, 63, 21};
	int size = 15;
	int i = 0;
	while (array[i])
		printf("%d ", array[i++]);
	ft_memset(array, 0, size);
	printf("\n");
	i = 0;
	while (i < 5)
		printf("%d ", array[i++]);
	printf("\n\n");

	char test[15] = "Bonjour a tous";
	int len = 7;
	printf("Avant memset : %s\n", test);
	ft_memset(test, 'a', len);
	printf("Après memset : %s\n", test);
	return (0);
}
*/
