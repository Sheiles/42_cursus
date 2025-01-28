/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:59:12 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/24 11:51:12 by sheiles          ###   ########.fr       */
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

// Define key codes 
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

// Define tile size
# define TILE_SIZE 64

typedef struct s_game {
    void *mlx;
    void *win;
    void *wall_img;
    void *player_img;
    void *collectible_img;
    void *exit_img;
    void *empty_img;
    int player_x;           
    int player_y;     
    int collectible_count; 
    char **map;            
} t_game;


// Map Parser
int     parse_map(const char *file, t_game *game);

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

void *get_next_line(int fd);
int close_window(t_game *game);

#endif /* SO_LONG_H */
