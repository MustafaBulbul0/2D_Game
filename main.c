#include "so_long.h"

char **read_map(t_game *game)
{
    char    **map;
    int     row_num;
    int     i;
    int     fd;

    i = -1;
    row_num = count_row(game);
    map = ft_calloc(row_num + 1, sizeof(char *));
    if (!map)
    shut_program_error(game);
    fd = open(game->file_name, O_RDONLY, 0777);
    while (++i < row_num)
        map[i] = get_next_line(fd);
    close(fd);
    game->screen_y = row_num * size;
    game->screen_x = ft_strlen(map[0]) * size;
    return (map);
}
t_game *init_game(char **argv)
{
    t_game  *new;

    new = ft_calloc(1, sizeof(t_game));
    if (!new)
        return (NULL);
    new->file_name = argv[1];
    new->mlx = mlx_init();
    new->map = read_map(new);
    return (new);
}

int main(int argc,char **argv)
{
    if(argc != 2)
        return (0);

    t_game *game;
    int color;

    game = init_game(argv);
    if (!game)
    return (-1);
    game->ptr_win = mlx_new_window(game->mlx, game->screen_x, game->screen_y, "mario");
    color = mlx_get_color_value(game->mlx, 0x0000FF);
    for (int y = 0; y < game->screen_y; y++)
    {
        for (int x = 0; x < game->screen_x; x++)
        {
            mlx_pixel_put(game->mlx, game->ptr_win, x, y, color);
        }
    }
    mlx_loop(game->mlx);

}