#include "../so_long.h"

static void	map_control1(t_game *control);
static void	map_control2(t_game *control);
static void	map_control3(t_game *control);

void	map_control(t_game *control)
{
	map_control1(control);
	map_control2(control);
	map_control3(control);
}

static void	map_control1(t_game *control)
{
	int		x;
	int		fd;
	int		count[2];
	char	*line;

	fd = open(control->file_name, O_RDONLY);
	if (fd < 0)
		shut_program_error(control);
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
	close(fd);
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
