#include "../so_long.h"

static void	free_textures(t_game *game);
static void	free_map(t_game *game);
static void	free_window(t_game *game);

void	shut_program_error(t_game *game)
{
	free_game(game);
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game);
	free_textures(game);
	free_window(game);
	if (game->file_name)
		free(game->file_name);
	free(game);
}

static void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

static void	free_textures(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->ground_img)
		mlx_destroy_image(game->mlx, game->ground_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->trap_img)
		mlx_destroy_image(game->mlx, game->trap_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
}

static void	free_window(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->ptr_win)
		mlx_destroy_window(game->mlx, game->ptr_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
