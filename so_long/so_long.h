
#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "mlx.h"
# include <sys/time.h>

# define TILE_SIZE 64

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*key[2];
	void	*exit[2];
	void	*player_right;
	void	*player_left;
} 	t_img;


typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	last_dir;
	int	width;
	int	height;
	int	player_x;
	int	player_y;
	int	keys;
	int	moves;
	int frame;

	struct timeval start_time;
	t_img	img;
} 	t_game;

// main.c
int		error(char *msg);

// map.c
int		load_map(t_game *game, char *filename);
void	free_map(t_game *game);
int		is_valid_map(t_game *game);

// events.c
int		handle_key(int keycode, t_game *game);
int		handle_exit(t_game *game);

// render.c
void	render_map(t_game *game);

// utils.c
size_t	sl_strlen(const char *s);
char	**sl_split(char const *s, char c);
void	sl_putstr_fd(char *s, int fd);

// exit.c
void	destroy_images(t_game *game);
int		handle_exit(t_game *game);

// path_check.c
int	check_valid_path(t_game *game);

// free_split.c
void	free_split(char **split);

#endif
