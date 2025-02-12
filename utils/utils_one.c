#include "../so_long.h"

t_game	*init_game(char *argv)
{
	t_game	*new;
    int     i;
    int     j;

    i = 0;
	new = ft_calloc(1, sizeof(t_game));
	if (!new)
		return (NULL);
	new->file_name = ft_strdup(argv);
	new->mlx = mlx_init();
	if (!new->mlx)
		shut_program_error(new);
	new->map = read_map(new);
	if (!new->map)
		shut_program_error(new);
    new->total_coin = 0;
    while (new->map[i])
    {
        j = 0;
        while (new->map[i][j])
        {
            if (new->map[i][j] == 'C')
                new->total_coin++;
            j++;
        }
        i++;
    }
	return (new);
}

char	**read_map(t_game *game)
{
	char	**map;
	int		row_num;
	int		i;
	int		fd;

	i = -1;
	row_num = count_row(game);
	map = ft_calloc(row_num + 1, sizeof(char *));
	if (!map)
		shut_program_error(game);
	fd = open(game->file_name, O_RDONLY);
	if (fd < 0)
    {
        if (map) 
            free(map);
        shut_program_error(game);
    }
	while (++i < row_num)
		map[i] = get_next_line(fd);
	close(fd);
	game->screen_y = row_num * SIZE;
	game->screen_x = (strlen(map[0]) - 1) * SIZE;
	return (map);
}

int	count_row(t_game *game)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(game->file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Invalid fd in count_row\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	count = 0;
	line = get_next_line(fd);
	while (line && line[0] != '\n')
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
