#include "../so_long.h"

t_game	*init_game(char *argv)
{
	t_game	*new;

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
	return (new);
}

int	count_row(t_game *game)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(game->file_name, O_RDONLY, 0777);
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

void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0
		|| new_y >= count_row(game)
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
			game->ground_img, game->player_x * 64, game->player_y * 64);
		game->player_x = new_x;
		game->player_y = new_y;
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->player_img, game->player_x * 64, game->player_y * 64);
		ft_printf("%d\n", ++game->counter);
	}
	if (new_x == game->exit_x && new_y == game->exit_y && game->total_coin == 0)
		exit(0);
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

//void	flood_fill(char **map, t_size size, t_game begin)
//{
//        map[begin.player_y][begin.player_x] = 1;
//	if (begin.player_y < 0 || begin.player_y >= size.y ||
//        begin.player_x < 0 || begin.player_x >= size.x 
//		|| map[begin.player_y][begin.player_x] == '1')
//		return ;
//	map[begin.player_y][begin.player_x] = '2';
//	flood_fill(map, size, (t_game){begin.player_x - 1, begin.player_y});
//	flood_fill(map, size, (t_game){begin.player_x + 1, begin.player_y});
//	flood_fill(map, size, (t_game){begin.player_x, begin.player_y - 1});
//	flood_fill(map, size, (t_game){begin.player_x, begin.player_y + 1});
//}
