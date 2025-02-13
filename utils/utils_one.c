#include "../so_long.h"

t_game	*init_game(char *argv)
{
	t_game	*new;
    int     i[2];

    i[0] = -1;
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
    while (new->map[++i[0]])
    {
        i[1] = -1;
        while (new->map[i[0]][++i[1]])
        {
            if (new->map[i[0]][i[1]] == 'C')
                new->total_coin++;
        }
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
	row_num = count_row(game->file_name);
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

int	count_row(char *file_name)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Invalid fd in count_row\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}


void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0
		|| new_y >= count_row(game->file_name)
		|| new_x >= (game->screen_x / SIZE))
		shut_program_error(game);
	if (game->map[new_y][new_x] == 'E' && game->total_coin > 0)
		return ;
	if (game->map[new_y][new_x] != '1')
	{
		if (game->map[new_y][new_x] == 'C')
		{
			game->total_coin--;
			game->map[new_y][new_x] = '0';
		}
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->ground_img, game->player_x * SIZE, game->player_y * SIZE);
		game->player_x = new_x;
		game->player_y = new_y;
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->player_img, game->player_x * SIZE, game->player_y * SIZE);
		ft_printf("%d\n", ++game->counter);
	}
	if (new_x == game->exit_x && new_y == game->exit_y && game->total_coin == 0)
		shut_program_success(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		shut_program_error(game);
	else if (keycode == 119)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 115)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == 97)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 100)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}
