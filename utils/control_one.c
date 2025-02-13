#include "../so_long.h"

static  void    map_control0(t_game *control);
static void	map_control1(t_game *control);
static void	map_control2(t_game *control);
static void	map_control3(t_game *control);

void	map_control(t_game *control)
{
    map_control0(control);
	map_control1(control);
	map_control2(control);
	map_control3(control);
    map_control4(control);
	//map_control5(control);
}

static  void    map_control0(t_game *control)
{
    char    **map;
    char    l;
    int     i[2];

    i[0] = -1;
    map = ft_strdup_2d((const char **)control->map);
    if (!map)
	{
	    clear_2d_pointer(map);
	    shut_program_error(control);
	}
    while (map[++i[0]])
    {
        i[1] = -1;
        while (map[i[0]][++i[1]])
        {
            l = map[i[0]][i[1]];
            if (l != 'E' && l != 'P' && l != '1' && l != '0' && l != 'C' && l != '\n')
            {
                clear_2d_pointer(map);
                shut_program_error(control);
            }
        }  
    }
    clear_2d_pointer(map);
}

static void	map_control1(t_game *control)
{
	int		count[4];
	char	*line;

	count[3] = open(control->file_name, O_RDONLY);
	if (count[3] < 0)
		shut_program_error(control);
	count[0] = 0;
	count[1] = 0;
	line = get_next_line(count[3]);
	while (line != NULL)
	{
		count[2] = -1;
		while (line[++count[2]] != '\0')
		{
			if (line[count[2]] == 'E')
				count[0]++;
			if (line[count[2]] == 'P')
				count[1]++;
		}
		free(line);
		line = get_next_line(count[3]);
	}
	close(count[3]);
	if (count[0] != 1 || count[1] != 1)
		shut_program_error(control);
}

static void	map_control2(t_game *control)
{
	char	**map;
	int		i;
	int		j;

	map = control->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (i == 0 && map[i][j] != '1')
				shut_program_error(control);
			if (i != 0 && i != ((control->screen_y / SIZE) - 1)
				&& (map[i][0] != '1'
				|| map[i][((control->screen_x / SIZE) - 1)] != '1'))
				shut_program_error(control);
			if (i == ((control->screen_y / SIZE) - 1) && map[i][j] != '1')
				shut_program_error(control);
			j++;
		}
		i++;
	}
}

static void	map_control3(t_game *control)
{
	char	**map;
	char	*f_name;
	int		i;

	if (control->total_coin <= 0)
        shut_program_error(control);
	map = control->map;
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != (control->screen_x / SIZE) + 1)
			shut_program_error(control);
		i++;
	}
	f_name = control->file_name;
	i = ft_strlen(f_name);
	if (f_name[i - 4] != '.' || f_name[i - 3] != 'b'
		|| f_name[i - 2] != 'e' || f_name[i - 1] != 'r')
		shut_program_error(control);
}
