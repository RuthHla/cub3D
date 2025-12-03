/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:02:45 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:07:02 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	long			i;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d > s)
	{
		i = len - 1;
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	else
		ft_memcpy(d, s, len);
	return (dest);
}
/*
#include <stdio.h>
int main()
{
	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};
	int i = 0;

	while (i < 7)
		printf("%i ", sResult[i++]);
	printf("\n");
	ft_memmove(sResult + 1, sResult, 2);
	i = 0;
	while (i < 7)
		printf("%i ", sResult[i++]);
	printf("\n");
}
*/
