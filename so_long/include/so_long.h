/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:56:56 by sheiles           #+#    #+#             */
/*   Updated: 2025/02/11 11:05:14 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "../minilibx-linux/mlx.h"
# include "../Libft/libft.h"
# include "../get_next_line/get_next_line.h"

// Key Codes
# define KEY_A       97
# define KEY_W      119
# define KEY_S      115
# define KEY_D      100
# define KEY_ESC  65307

# define XPM_WALL         "./textures/wall.xpm"

// Tile Size
# define TILE_SIZE   64

typedef struct s_game {
    void    *mlx;                 // Pointer to the MiniLibX instance
    void    *win;                 // Pointer to the game window
    void    *wall_img;            // Texture for wall tiles
    void    *player_img;          // Texture for the player character
    void    *collectible_img;     // Texture for collectibles
    void    *exit_img;            // Texture for the exit
    void    *empty_img;           // Texture for empty spaces
    int     player_x;             // Player's x-coordinate on the map
    int     player_y;             // Player's y-coordinate on the map
    int     collectible_count;    // Total number of collectibles remaining
    char    **map;                // 2D array representing the map
} t_game;

// Map Parser
int     parse_map(const char *file, t_game *game);
void    validate_map(t_game *game);

// Graphics
void    render_map(t_game *game);
void    load_textures(t_game *game);

// Input Handling
int     handle_key(int key, t_game *game);

// Game Logic
void    move_player(t_game *game, int x_offset, int y_offset);

// Utils
void    free_map(char **map);
void    error_exit(char *msg);

// Window Management
int     close_window(t_game *game);

#endif /* SO_LONG_H */
