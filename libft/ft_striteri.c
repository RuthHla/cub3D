/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:04:01 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:05:26 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
/*
#include <stdio.h>
void to_upper(unsigned int index, char *c)
{
    if (c && *c >= 'a' && *c <= 'z')
		*c -= 32;
}

int main()
{
    char str[] = "hello world!";
    printf("Avant : %s\n", str);
    ft_striteri(str, to_upper);
    printf("Après : %s\n", str);

    return 0;
}
*/
