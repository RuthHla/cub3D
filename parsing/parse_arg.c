#include "../cub.h"

int	check_arg(char *av)
{
	int fd = 0;
	size_t len;

	if (!av)
		return (print_error("Error\nMissing map file argument\n"), 0);

	len = ft_strlen(av);

	if (len < 5) // pcq au moins 1 lettre + .cub
		return (print_error("Error\nInvalid file name, expected atleast-> n.cub\n"), 0);

	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c' || av[len
		- 4] != '.')
		return (print_error("Error\nInvalid extension file name, expected -> .cub\n"), 0);

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nCannot open file\n"), 0);

	close(fd);
	return (1);
}
