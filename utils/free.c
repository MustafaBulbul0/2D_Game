#include "../so_long.h"

static void    free_game(t_game *game);

void    shut_program_error(t_game *game)
{
    free_game(game);
    ft_printf("Error\n");
    exit(EXIT_FAILURE);
}

static void    free_game(t_game *game)
{
    if (game->mlx)
        free(game->mlx);
    if (game->player_img)
        free(game->player_img);
    // to be 
}
