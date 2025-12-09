#include "../cub.h"

static void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**trim_n_split(char *line)
{
	char	*trimmed;
	char	**parts;
	int		i;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (print_error("Error\nMalloc failed\n"), NULL);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (print_error("Error\nMissing color values\n"), NULL);
	}
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		return (print_error("Error\nMalloc failed\n"), NULL);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return (print_error("Error\nInvalid color format\n"), NULL);
	}
	return (parts);
}

static int	parse_component(char *line, int *value)
{
	char	*comp;
	int		i;

	comp = ft_strtrim(line, " \t\n\v\f\r");
	if (!comp)
		return (print_error("Error\nMalloc failed\n"), 0);
	if (comp[0] == '\0')
	{
		free(comp);
		return (print_error("Error\nInvalid color component\n"), 0);
	}
	i = 0;
	while (comp[i])
	{
		if (!ft_isdigit((unsigned char)comp[i]))
		{
			free(comp);
			return (print_error("Error\nColor component must be a number\n"),
				0);
		}
		i++;
	}
	*value = ft_atoi(comp);
	free(comp);
	if (*value < 0 || *value > 255)
		return (print_error("Error\nColor component out of range [0,255]\n"),
			0);
	return (1);
}

int	parse_color(char *line, int *color)
{
	char	**parts;
	int		rgb[3];
	int		i;

	if (*color != -1)
		return (print_error("Error\nDuplicate color identifier\n"), 0);
	parts = trim_n_split(line);
	if (!parts)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!parse_component(parts[i], &rgb[i]))
		{
			free_split(parts);
			return (0);
		}
		i++;
	}
	free_split(parts);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}
