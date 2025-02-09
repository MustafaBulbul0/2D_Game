#include "so_long.h"

void move_player(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_y < 0 || new_y >= count_row(game) || new_x >= (int)strlen(game->map[new_y]))
        shut_program_error(game);
    if (game->map[new_y][new_x] != '1')
    {
        mlx_put_image_to_window(game->mlx, game->ptr_win, game->ground_img, game->player_x * 64, game->player_y * 64);
        game->player_x = new_x;
        game->player_y = new_y;
        mlx_put_image_to_window(game->mlx, game->ptr_win, game->player_img, game->player_x * 64, game->player_y * 64);
    }
    if (new_x == game->exit_x && new_y == game->exit_y)
        exit (0);
}

int key_press(int keycode, t_game *game)
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


void    write_map(t_game *game)
{
    int fd;
    int x = 0;
    int y = 0;
    int img_width = 0;
    int img_height = 0;
    char    *line;

    fd = open(game->file_name, O_RDONLY);
    if (fd < 0)
        shut_program_error(game);
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "image/wall.xpm", &img_width, &img_height);
    game->ground_img = mlx_xpm_file_to_image(game->mlx, "image/back_ground.xpm", &img_width, &img_height);
    game->collect_img = mlx_xpm_file_to_image(game->mlx, "image/coin.xpm", &img_width, &img_height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "image/exit.xpm", &img_width, &img_height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "image/player.xpm", &img_width, &img_height);
        
        if (!game->wall_img || !game->ground_img || !game->collect_img || !game->exit_img || !game->player_img)
    {
        close(fd);
        shut_program_error(game);
    }
    line = get_next_line(fd);
    while (line != NULL)
    {
        x = 0;
        while (line[x] != '\0')
        {
            if (line[x] == '1')
                mlx_put_image_to_window(game->mlx, game->ptr_win, game->wall_img, x*64, y*64);
            else if (line[x] == '0')
                mlx_put_image_to_window(game->mlx, game->ptr_win, game->ground_img, x*64, y*64);
            else if (line[x] == 'C')
                mlx_put_image_to_window(game->mlx, game->ptr_win, game->collect_img, x*64, y*64);
            else if (line[x] == 'E')
            {
                mlx_put_image_to_window(game->mlx, game->ptr_win, game->exit_img, x*64, y*64);
                game->exit_x = x;
                game->exit_y = y;
            }
            else if (line[x] == 'P')
            {
                mlx_put_image_to_window(game->mlx, game->ptr_win, game->player_img, x*64, y*64);
                game->player_x = x;
                game->player_y = y;
            }
            x++;
        }
        free(line);
        line = get_next_line(fd);
        y++;
    }
    close(fd);
}

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
    fd = open(game->file_name, O_RDONLY);
    if (fd < 0)
        shut_program_error(game);
    while (++i < row_num)
        map[i] = get_next_line(fd);
    close(fd);
    game->screen_y = row_num * size;
    game->screen_x = strlen(map[0]) * size;
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
    if (!new->mlx)
        shut_program_error(new);
    new->map = read_map(new);
    if (!new->map)
        shut_program_error(new);
    return (new);
}

int main(int argc,char **argv)
{
    if(argc != 2)
        return (1);

    t_game *game;

    game = init_game(argv);
    if (!game)
        return (-1);
    game->ptr_win = mlx_new_window(game->mlx, game->screen_x, game->screen_y, "mario");
    if (!game->ptr_win)
        shut_program_error(game);
    write_map(game);
    mlx_key_hook(game->ptr_win, key_press, game);

    mlx_loop(game->mlx);
}
