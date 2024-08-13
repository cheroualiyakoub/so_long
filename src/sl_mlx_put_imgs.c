/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_put_imgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:00:38 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/12 22:37:15 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Places the wall images on the game window according to the map data.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_images_walls(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;
	int				i;
	int				j;
	char			**map_array;

	mlx_game = game->sl_mlx_game;
	map_array = game->sl_map_array;
	i = -1;
	while (++i < game->sl_map_linges)
	{
		j = -1;
		while (++j < game->sl_map_lengh)
		{
			if (map_array[i][j] == game->sl_walls_char)
			{
				if (mlx_image_to_window(mlx_game->sl_mlx_handle,
						mlx_game->sl_mlx_wall_img,
						mlx_game->sl_mlx_w_img_size * j,
						mlx_game->sl_mlx_w_img_size * i) == -1)
					sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
			}
		}
	}
}

/**
 * Places the player image on the game window at its starting position.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_image_player(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	if (mlx_image_to_window(mlx_game->sl_mlx_handle,
			mlx_game->sl_mlx_player_img,
			game->sl_start_positon_y * mlx_game->sl_mlx_w_img_size,
			game->sl_start_positon_x * mlx_game->sl_mlx_w_img_size) == -1)
		sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
}

/**
 * Places the background image on the game window.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_image_background(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	if (mlx_image_to_window(mlx_game->sl_mlx_handle, \
			mlx_game->sl_mlx_backgrnd_img, 0, 0) == -1)
		sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
}

/**
 * Places the closed exit image on the game window.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_images_closed_exit(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	if (mlx_image_to_window(mlx_game->sl_mlx_handle,
			mlx_game->sl_mlx_cexit_img,
			game->sl_exit_positon_y * mlx_game->sl_mlx_w_img_size,
			game->sl_exit_positon_x * mlx_game->sl_mlx_w_img_size) == -1)
		sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
}

/**
 * Places the open exit image on the game window.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_images_open_exit(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	if (mlx_image_to_window(mlx_game->sl_mlx_handle,
			mlx_game->sl_mlx_oexit_img,
			game->sl_exit_positon_y * mlx_game->sl_mlx_w_img_size,
			game->sl_exit_positon_x * mlx_game->sl_mlx_w_img_size) == -1)
		sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
}
