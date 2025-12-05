#include "cub3d.h"

size_t	get_map_height(char *map_name)
{
	size_t	i;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (0);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}

char	**create_map_grid(char *map_name)
{
	int		fd;
	size_t	size;
	size_t	i;
	char	**map;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (0);
	size = get_map_height(map_name);
	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < size)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = 0;
	get_next_line(-1);
	close(fd);
	return (map);
}
