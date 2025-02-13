#include "../so_long.h"

static void	free_textures(t_game *game);
static void print_tux(int i);

void	shut_program_error(t_game *game)
{
	free_game(game);
	ft_printf("Error\n");
	print_tux(0);
	exit(EXIT_FAILURE);
}

void	shut_program_success(t_game *game)
{
	free_game(game);
	print_tux(1);
	exit(EXIT_SUCCESS);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	clear_2d_pointer(game->map);
	free_textures(game);
	if (!game->mlx)
		return ;
	if (game->ptr_win)
		mlx_destroy_window(game->mlx, game->ptr_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->file_name)
		free(game->file_name);
	free(game);
}

static void free_textures(t_game *game)
{
    if (game->mlx)
    {
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
}

static void print_tux(int i)
{
	if (i == 1)
	{
	ft_printf("             .--.  \n");
    ft_printf("            | ^_^ | \n");
    ft_printf("            |:_/  | \n");
    ft_printf("           //   \\ \\ \n");
    ft_printf("          (|     | ) \n");
    ft_printf("         /'\\_   _/`\\ \n");
    ft_printf("         \\___)=(___/ \n");
    ft_printf("<<<<<<<<<< CONGRATULATIONS >>>>>>>>>>\n");
	}
	else
	{
	ft_printf("             .--.  \n");
    ft_printf("            | T_T | \n");
    ft_printf("            |:_/  | \n");
    ft_printf("           //   \\ \\ \n");
    ft_printf("          (|     | ) \n");
    ft_printf("         /'\\_   _/`\\ \n");
    ft_printf("         \\___)=(___/ \n");
    ft_printf("<<<<<<<<<< FAILED >>>>>>>>>>\n");
	}
}
