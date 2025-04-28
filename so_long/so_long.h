/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:09:45 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 16:12:07 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include "mlx/mlx.h"

# define TILE_SIZE 24

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# define WALL '1'
# define FLOOR '0'
# define KEY 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*key[2];
	void	*exit[2];
	void	*player_left;
	void	*player_right;
}	t_img;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	int				keys;
	int				moves;
	int				frame;
	char			last_dir;
	struct timeval	start_time;
	t_img			img;
}	t_game;

typedef struct s_count
{
	int	players;
	int	exits;
	int	keys;
}	t_count;

/* event.c */
void	move_player(t_game *game, int new_x, int new_y);
int		handle_key(int keycode, t_game *game);

/* exit.c */
void	destroy_images(t_game *game);
int		handle_exit(t_game *game);

/* free_split.c */
void	free_split(char **split);

/* load_image.c */
void	load_images(t_game *game);

/* main.c */
int		error(char *msg);
void	game_init(t_game *game, char *mapfile);

/* map_checker.c */
int		is_valid_map(t_game *game);

/* map.c */
char	*read_file(char *filename);
int		load_map(t_game *game, char *filename);
void	free_map(t_game *game);

/* path_check.c */
int		check_valid_path(t_game *game);
char	**copy_map(char **map, int height);
void	flood_fill(char **map, int x, int y);

/* render.c */
void	draw_key(t_game *game, int x, int y);
void	draw_exit(t_game *game, int x, int y);
void	draw_player(t_game *game, int x, int y);
void	draw_tile(t_game *game, int x, int y);
void	render_map(t_game *game);

/* utilities.c */
size_t	sl_strlen(const char *s);
void	sl_putstr_fd(char *s, int fd);
int		word_count(const char *s, char c);
char	**sl_split(char const *s, char c);

#endif
