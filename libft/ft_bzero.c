/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:49:08 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:08:11 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = s;
	while (i < n)
	{
		*dest = (unsigned char) 0;
		i++;
		dest++;
	}
}
/*
#include <stdio.h>
int main()
{
        int array [] = { 54, 85, 20, 63, 21 };
        int size = 15;
        ft_bzero(array, size);
        for(int length = 0; length < 5; length++)
        {
                printf("%d ", array[length]);
        }
        return (0);
}
*/
