/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:01:25 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:07:53 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	int_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*tab;
	long	n;
	int		len;

	n = (long) nb;
	len = int_len(nb);
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	tab[len--] = '\0';
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		tab[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		tab[len] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	return (tab);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	(void) argc;
	int test = atoi(argv[1]);
	printf("%s\n", ft_itoa(test));
}
*/
