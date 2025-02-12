#include "./../so_long.h"

static char	**read_file(char *file_name);
static void	write_new_map(char **new_map, char *file_name);

void	map_man(char *file_name)
{
	int		row_num;
	char	**new_map;
	char	c;

	new_map = read_file(file_name);
	row_num = count_row(file_name);
	while (row_num > 0)
	{
		c = new_map[row_num - 1][0];
		if (!(c >= 9 && c <= 13) && c != 32)
			break ;
		free(new_map[row_num - 1]);
		new_map[row_num - 1] = NULL;
		row_num--;
	}
	write_new_map(new_map, file_name);
}

static char	**read_file(char *file_name)
{
	char	**map;
	int		row_num;
	int		i;
	int		fd;

	row_num = count_row(file_name);
	map = ft_calloc(row_num + 1, sizeof(char *));
	if (!map)
		exit(EXIT_FAILURE);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		clear_2d_pointer(map);
		return (NULL);
	}
	i = 0;
	while (i < row_num)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}

static void	write_new_map(char **new_map, char *file_name)
{
	int		fd;
	int		i;
	int		len;

	if (!new_map || !file_name)
		return ;
	fd = open(file_name, O_WRONLY | O_TRUNC);
	if (fd < 0)
		return ;
	i = 0;
	while (new_map[i])
	{
		if (new_map[i] != NULL)
		{
			len = ft_strlen(new_map[i]);
			write(fd, new_map[i], len);
			if (len > 0 && new_map[i][len - 1] != '\n')
				write(fd, "\n", 1);
		}
		free(new_map[i]);
		i++;
	}
	free(new_map);
	close(fd);
}
