#include "../so_long.h"

static void	map_control0(t_game *control, char **map);
static void	map_control1(t_game *control, char **map);
static void	map_control2(t_game *control);
static void	map_control3(t_game *control, char **map);

void	map_control(t_game *control)
{
	char	**map;

	map = ft_strdup_2d((const char **)control->map);
	if (!map)
	{
		clear_2d_pointer(map);
		shut_program_error(control);
	}
	map_control5(control);
	map_control0(control, map);
	map_control1(control, map);
	map_control3(control, map);
	clear_2d_pointer(map);
	map_control2(control);
	map_control4(control);
}

static void	map_control0(t_game *control, char **map)
{
	char	l;
	int		i[2];

	i[0] = -1;
	while (map[++i[0]])
	{
		i[1] = -1;
		while (map[i[0]][++i[1]])
		{
			l = map[i[0]][i[1]];
			if (l != 'E' && l != 'P' && l != '1' && l != '0' && l != 'C'
				&& l != '\n')
			{
				clear_2d_pointer(map);
				shut_program_error(control);
			}
		}
	}
}

static void	map_control1(t_game *control, char **map)
{
	int	count[4];

	count[3] = -1;
	count[0] = 0;
	count[1] = 0;
	while (map[++count[3]])
	{
		count[2] = -1;
		while (map[count[3]][++count[2]] != '\0')
		{
			if (map[count[3]][count[2]] == 'E')
				count[0]++;
			if (map[count[3]][count[2]] == 'P')
				count[1]++;
		}
	}
	if (count[0] != 1 || count[1] != 1)
	{
		clear_2d_pointer(map);
		shut_program_error(control);
	}
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
				&& (map[i][0] != '1' || map[i][((control->screen_x / SIZE)
					- 1)] != '1'))
				shut_program_error(control);
			if (i == ((control->screen_y / SIZE) - 1) && map[i][j] != '1')
				shut_program_error(control);
			j++;
		}
		i++;
	}
}

static void	map_control3(t_game *control, char **map)
{
	char	*f_name;
	int		i;

	if (control->total_coin <= 0)
	{
		clear_2d_pointer(map);
		shut_program_error(control);
	}
	i = -1;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) != (control->screen_x / SIZE) + 1)
		{
			clear_2d_pointer(map);
			shut_program_error(control);
		}
	}
	f_name = control->file_name;
	i = ft_strlen(f_name);
	if (f_name[i - 4] != '.' || f_name[i - 3] != 'b' || f_name[i - 2] != 'e'
		|| f_name[i - 1] != 'r')
	{
		clear_2d_pointer(map);
		shut_program_error(control);
	}
}
