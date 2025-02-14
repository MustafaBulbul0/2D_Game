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
	new->map = map_man(new->file_name);
    if (!new->map)
    {
        free(new->file_name);
        free(new);
        return (NULL);
    }
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
	new->screen_x = (i[1] - 1) * SIZE;
	new->screen_y = count_row(new->file_name) * SIZE;
	return (new);
}

int	count_row(char *file_name)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
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
