#include "../so_long.h"

int count_row(t_game *game)
{
    int     count;
    char    *line;
    int fd;

    fd = open(game->file_name, O_RDONLY, 0777);
    if (fd < 0)
    {
        ft_printf("Invalid fd in count_row\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (count);
}

