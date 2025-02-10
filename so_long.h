#ifndef SO_LONG
# define SO_LONG

# define size 64

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "library/get_next_line/get_next_line.h"
#include "minilibx/mlx.h"
#include "minilibx/mlx_int.h"
#include "library/ft_printf/ft_printf.h"
#include "library/libft/libft.h"

typedef struct s_game
{
    char **map;

    void *mlx;
    void *player_img;
    void *ground_img;
    void *wall_img;
    void *collect_img;
    void *trap_img;
    void *exit_img;
    void *ptr_win;

    int total_move;
    int total_collect;
    int screen_x;
    int screen_y;
    int player_x;
    int player_y;
    int exit_x;
    int exit_y;
    int counter;

    char *file_name;

} t_game;

void    shut_program_error(t_game *game);
int count_row(t_game *game);

#endif