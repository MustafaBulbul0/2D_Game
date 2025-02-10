#include "so_long.h"

int main(int argc,char **argv)
{
    t_game *game;
    
    if(argc != 2)
        return (1);
    game = init_game(argv);
    if (!game)
        return (-1);
    game->ptr_win = mlx_new_window(game->mlx, game->screen_x, game->screen_y, "mario");
    game->counter = 0;
    if (!game->ptr_win)
        shut_program_error(game);
    write_map(game);
    mlx_key_hook(game->ptr_win, key_press, game);
    mlx_loop(game->mlx);
}
