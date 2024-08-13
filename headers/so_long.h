/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:21:00 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:19:47 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../Libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_sl_messages
{
	char	*sl_err_path;
	char	*sl_err_png_path;
	char	*sl_err_file_name;
	char	*sl_err_extension;
	char	*sl_err_malloc;
	char	*sl_err_map_rectangular;
	char	*sl_err_invalid_char;
	char	*sl_err_map_to_small;
	char	*sl_err_map_player;
	char	*sl_err_map_exit;
	char	*sl_err_map_count_collectible;
	char	*sl_err_map_walls;
	char	*sl_err_map_rich_collectible;
	char	*sl_err_map_rich_exit;
	char	*sl_movement_prompt;
	char	*sl_mlx_resize_img;
	char	*sl_mlx_err_size_monitor;
}	t_sl_messages;

typedef struct sl_mlx_coll_imgs
{
	mlx_image_t					*sl_mlx_coll_img;
	uint32_t					x;
	uint32_t					y;
	struct sl_mlx_coll_imgs		*next;
}	t_sl_mlx_coll_imgs;

typedef struct sl_mlx_game
{
	char				*mlx_game_name;
	mlx_t				*sl_mlx_handle;
	int					sl_mlx_window_width;
	int					sl_mlx_window_height;
	char				*sl_mlx_p_img_path;
	char				*sl_mlx_oe_img_path;
	char				*sl_mlx_ce_img_path;
	char				*sl_mlx_c_img_path;
	char				*sl_mlx_w_img_path;
	char				*sl_mlx_b_img_path;
	uint32_t			sl_mlx_w_img_size;
	uint32_t			sl_mlx_p_img_size;
	uint32_t			sl_mlx_e_img_size;
	uint32_t			sl_mlx_c_img_size;
	uint32_t			sl_mlx_b_img_size_x;
	uint32_t			sl_mlx_b_img_size_y;
	mlx_image_t			*sl_mlx_player_img;
	mlx_image_t			*sl_mlx_oexit_img;
	mlx_image_t			*sl_mlx_cexit_img;
	mlx_image_t			*sl_mlx_backgrnd_img;
	mlx_image_t			*sl_mlx_wall_img;
	t_sl_mlx_coll_imgs	**sl_colls_imgs;
}	t_sl_mlx_game;

typedef struct s_sl_game
{
	char			*sl_map_path;
	char			*sl_map_path_extension;
	t_list			*sl_map;
	int				sl_map_max_size_width;
	int				sl_map_max_size_height;
	int				*sl_map_max_size;
	t_sl_messages	*sl_messages;
	char			sl_player_char;
	char			sl_exit_char;
	char			sl_collectible_char;
	int				sl_count_collectible;
	int				sl_walls_char;
	int				sl_empty_char;
	int				sl_map_linges;
	int				sl_map_lengh;
	char			**sl_map_array;
	char			**sl_map_temp;
	int				sl_start_positon_x;
	int				sl_start_positon_y;
	int				sl_exit_positon_x;
	int				sl_exit_positon_y;
	int				sl_count_coll_temp;
	int				sl_eated_coll;
	int				sl_game_ended;
	int				sl_riched_exit;
	int				sl_count_movements;
	keys_t			sl_key_up;
	keys_t			sl_key_down;
	keys_t			sl_key_left;
	keys_t			sl_key_right;
	t_sl_mlx_game	*sl_mlx_game;
}	t_sl_game;

// Init game
void		sl_init_config(t_sl_game *game);
void		sl_init_messages(t_sl_game *game);
void		sl_init_messages_2(t_sl_game *game);
void		sl_init_mlx_game(t_sl_game *game);

/// map
void		sl_set_map_to_game(t_sl_game *game);
int			sl_check_map_path(t_sl_game *game);
void		sl_read_map(t_sl_game *game);
void		sl_check_map_chars(t_sl_game *game);
void		sl_check_player(t_sl_game *game);
void		sl_map_check_exit(t_sl_game *game);
void		sl_check_rich_exit(t_sl_game *game);
void		sl_map_count_collectible(t_sl_game *game);
void		sl_check_map_rectangular(t_sl_game *game);
void		sl_set_array_map(t_sl_game *game);
void		sl_map_chek_walls(t_sl_game *game);
int			sl_is_valid_char(t_sl_game *game, char c);
void		sl_rich_coll_exit(t_sl_game *game);
void		sl_flood_fill(t_sl_game *game, int index_x, int index_y);
void		sl_set_start_positions(t_sl_game *game);
void		sl_set_temp_map(t_sl_game *game);
void		sl_put_images_colls(t_sl_game *game);

// MLX game
int32_t		sl_mlx_start_game(t_sl_game *game);
void		sl_create_handle(t_sl_game *game);
void		sl_mlx_load_images(t_sl_game *game);
void		sl_load_images_colls(t_sl_game *game);
void		sl_resize_images(t_sl_game *game);
void		ft_hook(mlx_key_data_t keydata, void *param);
int			sl_mlx_move(t_sl_game *game, mlx_instance_t *ins, int x, int y);
int			sl_mlx_can_move(t_sl_game *game, int x, int y);
void		sl_put_images_walls(t_sl_game *game);
void		sl_put_image_player(t_sl_game *game);
void		sl_put_image_background(t_sl_game *game);
void		sl_put_images_closed_exit(t_sl_game *game);
void		sl_put_images_open_exit(t_sl_game *game);
mlx_image_t	*sl_mlx_load_png(t_sl_game *game, char *sl_img_path);
void		sl_mlx_resize_image(t_sl_game *game, \
				mlx_image_t *img, uint32_t x, uint32_t y);
void		sl_check_game_size(t_sl_game *game);

// exit
void		sl_clean_exit(t_sl_game *game, char *msg);
void		sl_clean(t_sl_game *game);
void		sl_mlx_clean_coll_imgs(t_sl_mlx_game *mlx_game);
void		sl_clean_mlx(t_sl_mlx_game *mlx_game);

#endif