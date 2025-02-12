#include "./../so_long.h"

void	flood_fill(char **map, t_size size, t_size begin)
{
	if (map[begin.y][begin.x] == 'E')
	{
		map[begin.y][begin.x] = 'F';
		return;
	}
	if (begin.y < 0 || begin.y >= size.y
		|| begin.x < 0 || begin.x >= size.x
		|| map[begin.y][begin.x] == '1'
		|| map[begin.y][begin.x] == 'F')
		return;

	map[begin.y][begin.x] = 'F';
	flood_fill(map, size, (t_size){begin.x - 1, begin.y});
	flood_fill(map, size, (t_size){begin.x + 1, begin.y});
	flood_fill(map, size, (t_size){begin.x, begin.y - 1});
	flood_fill(map, size, (t_size){begin.x, begin.y + 1});
}

void player_init(t_game *control)
{
	int i;
	int j;

	i = 0;
	while (control->map[i])
	{
		j = 0;
		while (control->map[i][j])
		{
			if (control->map[i][j] == 'P')
			{
				control->player_x = j;
				control->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	map_control4(t_game *game)
{
	char	**map;
	t_size	size;
	t_size	begin;
	int		i[2];

	map = ft_strdup_2d((const char **)game->map);
	if (!map)
		return;
	player_init(game);
	size.x = game->screen_x / SIZE;
	size.y = game->screen_y / SIZE;
	begin.x = game->player_x;
	begin.y = game->player_y;
	flood_fill(map, size, begin);
	i[0] = -1;
	while (map[++i[0]])
	{
		i[1] = -1;
		while (map[i[0]][++i[1]])
		{
			if (!(map[i[0]][i[1]] == 'F' || map[i[0]][i[1]] == '1' || map[i[0]][i[1]] == '\n'))
				shut_program_error(game);
		}
	}
	clear_2d_pointer(map);
}
