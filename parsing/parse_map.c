/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:09 by alandel           #+#    #+#             */
/*   Updated: 2025/12/10 10:35:10 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// normaliser la map (remplacer le vide ar des espaces pour parcour un rectangle)
// autoriser seulement : '0', '1', ' ', 'N', 'S', 'E', 'W'
// uniquement 1 player
// Vérifier que la map est fermée (un 0 ne peux pas etre adjacent a un ' ')

// data->map : tableau de lignes déjà lu
// data->map_h : nb de lignes
// data->map_w : longueur max

int	normalize_map(t_data *data)
{
	char	**rect;
	int		len;

	int i, j;
	rect = malloc(sizeof(char *) * (data->map_h + 1));
	if (!rect)
		return (print_error("Error\nMalloc failed\n"), 0);
	i = 0;
	while (i < data->map_h)
	{
		rect[i] = malloc(data->map_w + 1);
		if (!rect[i])
			return (print_error("Error\nMalloc failed\n"), 0);
		len = ft_strlen(data->map[i]);
		j = 0;
		while (j < data->map_w)
		{
			if (j < len)
				rect[i][j] = data->map[i][j];
			else
				rect[i][j] = ' ';
			j++;
		}
		rect[i][j] = '\0';
		i++;
	}
	rect[i] = NULL;
	// free ancienne map
	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	data->map = rect;
	return (1);
}

int	parse_player_and_chars(t_data *data)
{
	int		player_count;
	char	c;
	int		i;
	int		j;

	player_count = 0;
	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			c = data->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				data->player_x = j + 0.5;
				data->player_y = i + 0.5;
				// set_player_dir_from_char(data, c);
				data->map[i][j] = '0'; // case walkable ou conserver lettre ?
			}
			else if (c != '0' && c != '1' && c != ' ')
				return (print_error("Error\nInvalid char in map\n"), 0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Error\nMap must have exactly one player\n"), 0);
	return (1);
}

int	is_closed_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			if (data->map[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == data->map_h - 1 || j == data->map_w
					- 1)
					return (print_error("Error\nMap not closed\n"), 0);
				if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
					|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
					return (print_error("Error\nMap not closed\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_map(t_data *data)
{
	if (!normalize_map(data))
		return (0);
	if (!parse_player_and_chars(data))
		return (0);
	if (!is_closed_map(data))
		return (0);
	return (1);
}
