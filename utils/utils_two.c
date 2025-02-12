#include "./../so_long.h"

void	write_map(t_game *game)
{
	int		fd;
	int		img_width;
	int		img_height;
	char	*line;

	img_width = 0;
	img_height = 0;
	fd = open(game->file_name, O_RDONLY);
	if (fd < 0)
		shut_program_error(game);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "image/wall.xpm",
			&img_width, &img_height);
	game->ground_img = mlx_xpm_file_to_image(game->mlx, "image/back_ground.xpm",
			&img_width, &img_height);
	game->collect_img = mlx_xpm_file_to_image(game->mlx, "image/coin.xpm",
			&img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "image/exit.xpm",
			&img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "image/player.xpm",
			&img_width, &img_height);
	if (!game->wall_img || !game->ground_img || !game->collect_img
		|| !game->exit_img || !game->player_img)
	{
		close(fd);
		shut_program_error(game);
	}
	line = get_next_line(fd);
	write_map_2(game, line, fd);
	close(fd);
}

void	write_map_2(t_game *game, char *line, int fd)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (line != NULL)
	{
		x = 0;
		while (line[x] != '\0')
		{
			write_map_3(game, line, x, y);
			x++;
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
}

void	write_map_3(t_game *game, char *line, int x, int y)
{
	if (line[x] == '1')
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->wall_img, x * 64, y * 64);
	else if (line[x] == '0')
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->ground_img, x * 64, y * 64);
	else if (line[x] == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->collect_img, x * 64, y * 64);
	}
	else if (line[x] == 'E')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->exit_img, x * 64, y * 64);
		game->exit_x = x;
		game->exit_y = y;
	}
	else if (line[x] == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->player_img, x * 64, y * 64);
		game->player_x = x;
		game->player_y = y;
	}
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
