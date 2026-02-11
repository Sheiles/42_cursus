#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "Libft/libft.h"
# include <mlx.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define FOV 66
# define ROTATION_SPEED 0.05
# define MOVE_SPEED 0.05

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	fov;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	double	distance;
	int		wall_direction;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_length;
	int			endian;
	t_player	player;
	t_map		map;
	t_texture	no_texture;
	t_texture	so_texture;
	t_texture	we_texture;
	t_texture	ea_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	int			width;
	int			height;
}	t_game;

/* PARSING FUNCTIONS */
int		parse_cub_file(char *filename, t_game *game);
int		parse_no_texture(char *line, t_game *game);
int		parse_so_texture(char *line, t_game *game);
int		parse_we_texture(char *line, t_game *game);
int		parse_ea_texture(char *line, t_game *game);
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);
int		parse_map(char *filename, t_game *game, int start_line);
int		validate_map(t_game *game);

/* RAYCASTING FUNCTIONS */
void	raycaster(t_game *game);
double	cast_ray(t_game *game, double angle);
int		get_wall_direction(t_game *game, double hit_x, double hit_y);

/* RENDERING FUNCTIONS */
void	render_frame(t_game *game);
void	draw_wall_slice(t_game *game, int x, double distance, int wall_dir);
void	put_pixel(t_game *game, int x, int y, int color);
int		get_color_from_texture(t_texture *tex, int x, int y);

/* EVENT HANDLING */
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		close_window(t_game *game);

/* UTILITY FUNCTIONS */
void	error_exit(char *message);
void	init_game(t_game *game);
void	cleanup_game(t_game *game);
int		is_wall(t_game *game, double x, double y);

/* KEY CODES (typical minilibX) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

#endif
