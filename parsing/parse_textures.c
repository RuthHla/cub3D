/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:06 by alandel           #+#    #+#             */
/*   Updated: 2025/12/10 10:35:07 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);

	if (len < 5) // pcq au moins 1 lettre + .xpm
		return (print_error("Error\nInvalid xpm file,expected atleast-> n.xpm\n"), 0);
	if (path[len - 1] != 'm' || path[len - 2] != 'p' || path[len - 3] != 'x'
		|| path[len - 4] != '.')
	{
		print_error("Error\nInvalid xpm file,expected atleast-> n.xpm\n");
		return (0);
	}
	return (1);
}

int	parse_texture(char *line, char **texture)
{
	char *path;

	if (*texture != NULL) // penser a free le reste si besoin
		return (print_error("Error\nDuplicate texture identifier\n"), 0);

	path = ft_strtrim(line, " \t\n\v\f\r");
	if (!path)
		return (print_error("Error\nMalloc failed\n"), 0);
	if (path[0] == '\0')
	{
		free(path);
		return (print_error("Error\nMissing texture path\n"), 0);
	}

	if(!check_extension(path))
	{
		free(path);	
		return(0);
	}
	*texture = path;
	return (1);
}