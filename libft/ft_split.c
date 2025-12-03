/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:31:05 by sleroy            #+#    #+#             */
/*   Updated: 2024/11/26 11:05:42 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char c, char sep)
{
	if (c == sep || c == '\0')
		return (1);
	return (0);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (!check_char(s[i], c) && check_char(s[i + 1], c))
			words++;
		i++;
	}
	return (words);
}

static char	*word_split(char const *s, char c)
{
	char	*word;
	int		word_len;
	int		i;

	i = 0;
	word_len = 0;
	while (!check_char(s[i], c))
	{
		i++;
		word_len++;
	}
	word = malloc(sizeof(char) * (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (!check_char(s[i], c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;

	words = word_count(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (check_char(*s, c))
			s++;
		tab[i] = word_split(s, c);
		if (!tab[i])
		{
			free_tab(tab, i);
			return (NULL);
		}
		while (!check_char(*s, c))
			s++;
		i++;
	}
	tab[words] = 0;
	return (tab);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	char *str = argv[1];
	char sep = argv[2][0];
	char **tab = ft_split(str, sep);
	int words = word_count(str, sep);
	int i = 0;
	while (i < words)
		printf("%s\n", tab[i++]);
	return (0);
}
*/
