#include "../so_long.h"

static void map_control2(t_game *control);
static void    map_control3(t_game *control);

void map_control(t_game *control)
{
    int x;
    int fd;
    int count[2];
    char    *line;

    fd = open (control->file_name, O_RDONLY);
    count[0] = 0;
    count[1] = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        x = -1;
        while (line[++x] != '\0')
        {
            if (line[x] == 'E')
                count[0]++;
            if (line[x] == 'P')
                count[1]++;
        }
        free(line);
        line = get_next_line(fd);
    }
    if (count[0] != 1 || count[1] != 1)
        shut_program_error(control);
    map_control2(control);
}

static void map_control2(t_game *control)
{
    char    **map;
    int     i;
    int     j;

    map = control->map;
    i = 0;
    while (map[i])
    {
        j = 0; 
        while (map[i][j] != '\n' && map[i][j] != '\0')
        {
            if (i == 0 && map[i][j] != '1')
                shut_program_error(control);            
            if (i != 0 && (i != ((control->screen_y) / SIZE) - 1)
                && (map[i][0] != '1'
                || map[i][((control->screen_x) / SIZE) - 1] != '1'))
                shut_program_error(control);
            if (i == (((control->screen_y) / SIZE) - 1)&& map[i][j] != '1')
                shut_program_error(control);
            j++;
        }
        i++;
    }
    map_control3(control);
}

static void    map_control3(t_game *control)
{
    char    **map;
    int     i;

    map = control->map;
    i = 0;
    while (map[i])
    {
        if ((int)ft_strlen(map[i]) != (control->screen_x / SIZE) + 1)
        {
            ft_printf("%d %d\n", control->screen_x / 64, (int)ft_strlen(map[i]));
            shut_program_error(control);
        }
        i++;
    }
}
