/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:03:29 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 19:36:59 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cmp;
	unsigned char	*s2_cmp;
	size_t			i;

	s1_cmp = (unsigned char *)s1;
	s2_cmp = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_cmp[i] < s2_cmp[i])
			return (-1);
		else if (s1_cmp[i] > s2_cmp[i])
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char s1[] = {-128, 0, 127, 0};
	char s2[] = {-128, 0, 127, 0};
	size_t n = 4;
	printf("%i\n", memcmp(s1, s2, n));
	printf("%i\n", ft_memcmp(s1, s2, n));

	printf("\n");

	char t1[15] = "Bonjour a tous";
	char t2[17] = "Bonjour la tchim";
	size_t len = 10;
	printf("%i\n", memcmp(t1, t2, len));
	printf("%i\n", ft_memcmp(t1, t2, len));

}
*/
