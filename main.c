#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	t_game	*control;

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
			game->screen_y, "mario");
	game->counter = 0;
	if (!game->ptr_win)
		shut_program_error(game);
	write_map(game);
	mlx_key_hook(game->ptr_win, key_press, game);
	mlx_loop(game->mlx);
}
