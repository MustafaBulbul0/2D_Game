#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 64

# include <unistd.h>
# include <fcntl.h>
# include "library/get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include "library/ft_printf/ft_printf.h"
# include "library/libft/libft.h"

typedef struct s_game
{
	char	**map;
	char	*file_name;
	void	*mlx;
	void	*player_img;
	void	*ground_img;
	void	*wall_img;
	void	*collect_img;
	void	*trap_img;
	void	*exit_img;
	void	*ptr_win;
	int		total_move;
	int		total_collect;
	int		screen_x;
	int		screen_y;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		counter;
	int		total_coin;
}	t_game;

typedef struct s_size
{
	int	x;
	int	y;
}	t_size;

void	shut_program_success(t_game *game);
void	shut_program_error(t_game *game);
int		count_row(char *file_name);
int		key_press(int keycode, t_game *game);
t_game	*init_game(char *argv);
void	write_map(t_game *game);
char	**read_map(t_game *game);
void	map_control(t_game *control);
void	map_control4(t_game *game);
char    **map_man(char *file_name);
void	free_game(t_game *game);
void map_control5(t_game *game);

#endif
