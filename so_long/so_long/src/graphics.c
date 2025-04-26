/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:18 by sheiles           #+#    #+#             */
/*   Updated: 2025/02/11 11:38:56 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../minilibx-linux/mlx.h"

void load_textures(t_game *game)
{
    int size;

    size = TILE_SIZE;
    printf("Loading wall texture...\n");
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &size, &size);
    if (!game->wall_img)
        error_exit("Failed to load wall texture");
    printf("Loading player texture...\n");
    game->player_img = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm", &size, &size);
    if (!game->player_img)
        error_exit("Failed to load player texture");
    printf("Loading collectible texture...\n");
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "./textures/coolectible.xpm", &size, &size);
    if (!game->collectible_img)
        error_exit("Failed to load collectible texture");
    printf("Loading exit texture...\n");
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &size, &size);
    if (!game->exit_img)
        error_exit("Failed to load exit texture");
    printf("Loading empty texture...\n");
    game->empty_img = mlx_xpm_file_to_image(game->mlx, "./textures/empty.xpm", &size, &size);
    if (!game->empty_img)
        error_exit("Failed to load empty texture");
    printf("Textures loaded successfully!\n");
}