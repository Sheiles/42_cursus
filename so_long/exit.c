#include "so_long.h"
#include <sys/time.h>

void destroy_images(t_game *game)
{
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.key)
		mlx_destroy_image(game->mlx, game->img.key);
	if (game->img.exit)
		mlx_destroy_image(game->mlx, game->img.exit);
	if (game->img.player)
		mlx_destroy_image(game->mlx, game->img.player);
}
int handle_exit(t_game *game)
{
	struct timeval end_time;
	long elapsed_sec;

	gettimeofday(&end_time, NULL);
	elapsed_sec = end_time.tv_sec - game->start_time.tv_sec;

	printf("Total moves: %d\n", game->moves);
	printf("Total time: %ld seconds\n", elapsed_sec);

	destroy_images(game);
	free_map(game);
	exit(0);
	return (0);
}

