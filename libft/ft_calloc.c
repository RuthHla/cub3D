/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:01 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/21 10:07:07 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	bytes;

	bytes = nmemb * size;
	if (size != 0 && (bytes / size) != nmemb)
		return (NULL);
	mem = malloc(bytes);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, bytes);
	return (mem);
}
