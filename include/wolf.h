/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 19:59:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 14:23:27 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

typedef struct		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_double_pos
{
	double			x;
	double			y;
}					t_double_pos;

typedef struct		s_int_pos
{
	int				x;
	int				y;
}					t_int_pos;

typedef struct		s_camera
{
	double			height;
	t_double_pos	dir;
	t_double_pos	pos;
	t_double_pos	plane;
}					t_camera;

typedef struct		s_texture
{
	void			*img;
	char			*ptr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*ptr;
	int				bpp;
	int				size_line;
	int				endian;
	int				**map;
	int				map_height;
	int				map_width;
	t_int_pos		wall;
	int				side;
	t_double_pos	ray_dir;
	t_int_pos		red;
	t_int_pos		blue;
	int				sidered;
	int				sideblue;
}					t_env;

typedef struct		s_dda
{
	t_double_pos	*side_dist;
	t_double_pos	*delta_dist;
	t_int_pos		*step;
	t_double_pos	*ray_dir;
	int				x;
}					t_dda;

typedef struct		s_key
{
	int				up;
	int				down;
	int				left;
	int				right;
}					t_key;

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 800
# define WALL_p_WIDTH 420
# define WALL_p_HEIGHT 420
# define PORTAL_GUN_WIDTH 561
# define PORTAL_GUN_HEIGHT 347
# define WALL_HEIGHT 250
# define SIZE_BLOCK 64
# define PI 3.14159265
# define DISTANCE_CAMERA_SCREEN (SCREEN_WIDTH / 2) / tan(30)
# define ANGLE_ENTRE_DEUX_RAYONS_CONSECUTIFS 60 / SCREEN_WIDTH
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L << 6)
# define KEYPRESSMASK (1L << 0)
# define KEYRELEAMASK (1L << 1)
# define KEYPRESS 2
# define KEYRELEA 3
# define KEY_TAB 48
# define KEY_ESCAPE 53
# define BUTTONPRESS 4
# define BUTTON1 1
# define BUTTON2 2
# define BUTTON3 3
# define BUTTON4 4
# define BUTTON5 5
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_B 11
# define KEY_PAD_SUB 78
# define KEY_PAD_ADD 69
# define KEY_R 15
# define KEY_Z 6
# define KEY_H 4
# define KEY_S 1

int					init_env(char *file);
void				ft_parse_input(char *name);
void				ft_trace_colone(int x, double dist_wall, t_double_pos ray_dir);
void				ft_pixelput(int x, int y, int color);
t_env				*env(void);
int					ft_retmsg(char *message, int sortie);
void				ft_exit(char *message, int sortie);
void				display_map(void);
void				init_cam(void);
t_camera			*cam(void);
void				ft_wolf(void);
int					ft_hit(double proj, int portal, t_dda dda);

t_texture			*texture(void);
t_texture			*gun(void);
t_texture			*portal_blue(void);
t_texture			*portal_red(void);
int					init_portal_blue_texture(void);
int					init_portal_red_texture(void);
int					init_portal_gun_texture(void);
int					init_wall_texture(void);

unsigned int		ft_pixelget(int x, int y, t_texture t);
int					ft_move(void *param);
void				floor_casting(int x, double dist_wall, int y);
int					ft_key_pressed(int keycode, void *param);
t_key				*key(void);
int					ft_key_release(int keycode, void *param);
void				trace_portail(int x, double dist_wall, int portal);
unsigned int		ft_pixelget_img(int x, int y);
void				portal_gun_shoot(int keycode);
void				teleport_pos(int portal);
int					transform_sidecolor(int side_color);
void				cross();
void				draw_portal_gun(void);

void				ft_rev_rot_int(t_int_pos *a);
void				ft_rev_rot_double(t_double_pos *a);
void				ft_rot_int(t_int_pos *a);
void				ft_rot_double(t_double_pos *a);
void				ft_swap_int_pos(t_int_pos *a);
void				ft_swap_double_pos(t_double_pos *a);

int					good_side_portal(t_int_pos *step, int side_color);
int					transform_sidecolor(int side_color);
double				ft_min_double(double a, double b);
void				transform_direction_ray_portal(int portal, t_dda dda);

void				ft_init_dist(t_dda dda);

#endif
