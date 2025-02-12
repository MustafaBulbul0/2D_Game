#include "./../so_long.h"

static void write_map_1(t_game *game);
static void	write_map_2(t_game *game, char *line, int fd);
static void	write_map_3(t_game *game, char *line, int x, int y);

void	write_map(t_game *game)
{
	int		fd;
	char	*line;

	fd = open(game->file_name, O_RDONLY);
	if (fd < 0)
		shut_program_error(game);
	write_map_1(game);	
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

static void write_map_1(t_game *game)
{
	int		img_width;
	int		img_height;
	
	img_width = 0;
	img_height = 0;
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
}

static void	write_map_2(t_game *game, char *line, int fd)
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

static void	write_map_3(t_game *game, char *line, int x, int y)
{
	if (line[x] == '1')
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->wall_img, x * SIZE, y * SIZE);
	else if (line[x] == '0')
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->ground_img, x * SIZE, y * SIZE);
	else if (line[x] == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->collect_img, x * SIZE, y * SIZE);
	}
	else if (line[x] == 'E')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->exit_img, x * SIZE, y * SIZE);
		game->exit_x = x;
		game->exit_y = y;
	}
	else if (line[x] == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->ptr_win,
			game->player_img, x * SIZE, y * SIZE);
		game->player_x = x;
		game->player_y = y;
	}
}
