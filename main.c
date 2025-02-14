#include "so_long.h"

static int	shut_program_error2(void *new);

int	main(int argc, char **argv)
{
	t_game	*control;
	t_game	*game;

	if (argc != 2)
		return (1);
	control = init_game(argv[1]);
	if (!control)
		return (-1);
	map_control(control);
	free_game(control);
	game = init_game(argv[1]);
	if (!game)
		return (-1);
	game->ptr_win = mlx_new_window(game->mlx, game->screen_x,
			game->screen_y, "MARIO");
	if (!game->ptr_win)
		shut_program_error(game);
	write_map(game);
	mlx_key_hook(game->ptr_win, key_press, game);
	mlx_hook(game->ptr_win, 17, 0, shut_program_error2, game);
	mlx_loop(game->mlx);
	mlx_loop(game->mlx);
}

static int	shut_program_error2(void *new)
{
	t_game	*game;

	game = (t_game *)new;
	shut_program_error(game);
	return (0);
}
