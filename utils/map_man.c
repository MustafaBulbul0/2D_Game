#include "./../so_long.h"

static char	**read_file(char *file_name, int row_num);
static char	*n_line(char *line);
char		**map_man(t_game *game);

static char	*n_line(char *line)
{
	char	*new_line;
	size_t	len;

	len = ft_strlen(line);
	if (!line || len == 0 || line[len - 1] == '\n')
		return (line);
	new_line = (char *)ft_calloc(len + 2, sizeof(char));
	if (!new_line)
	{
		free(line);
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new_line, line, len + 1);
	new_line[len] = '\n';
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

static char	**read_file(char *file_name, int row_num)
{
	char	**map;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	map = ft_calloc(row_num + 1, sizeof(char *));
	if (!map)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free(map);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line && i < row_num)
	{
		if (line[0] != '\n')
		{
			line = n_line(line);
			map[i++] = line;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

char	**map_man(t_game *game)
{
	char	**map;
	int		c_row;

	c_row = count_row(game);
	if (c_row <= 0)
		shut_program_error(game);
	map = read_file(game->file_name, c_row);
	return (map);
}
