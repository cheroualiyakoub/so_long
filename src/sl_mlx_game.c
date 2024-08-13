/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:17:21 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:37:28 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Initializes the MLX handle and window with the given dimensions.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_create_handle(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;
	mlx_t			*sl_mlx_handle;

	mlx_game = game->sl_mlx_game;
	sl_mlx_handle = \
		mlx_init(mlx_game->sl_mlx_window_width, \
		mlx_game->sl_mlx_window_height, mlx_game->mlx_game_name, true);
	if (!(sl_mlx_handle))
		sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
	mlx_game->sl_mlx_handle = sl_mlx_handle;
}

/**
 * Loads the images for the game elements from their respective paths.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_mlx_load_images(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	mlx_game->sl_mlx_player_img = sl_mlx_load_png(game, \
		mlx_game->sl_mlx_p_img_path);
	mlx_game->sl_mlx_wall_img = sl_mlx_load_png(game, \
		mlx_game->sl_mlx_w_img_path);
	mlx_game->sl_mlx_backgrnd_img = sl_mlx_load_png(game, \
		mlx_game->sl_mlx_b_img_path);
	mlx_game->sl_mlx_cexit_img = sl_mlx_load_png(game, \
		mlx_game->sl_mlx_ce_img_path);
	mlx_game->sl_mlx_oexit_img = sl_mlx_load_png(game, \
		mlx_game->sl_mlx_oe_img_path);
}

/**
 * Resizes the loaded images to their specified dimensions.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_resize_images(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	sl_mlx_resize_image(game, mlx_game->sl_mlx_player_img, \
		mlx_game->sl_mlx_p_img_size, mlx_game->sl_mlx_p_img_size);
	sl_mlx_resize_image(game, mlx_game->sl_mlx_wall_img, \
		mlx_game->sl_mlx_w_img_size, mlx_game->sl_mlx_w_img_size);
	sl_mlx_resize_image(game, mlx_game->sl_mlx_backgrnd_img, \
		mlx_game->sl_mlx_b_img_size_x, mlx_game->sl_mlx_b_img_size_y);
	sl_mlx_resize_image(game, mlx_game->sl_mlx_oexit_img, \
		mlx_game->sl_mlx_e_img_size, mlx_game->sl_mlx_e_img_size);
	sl_mlx_resize_image(game, mlx_game->sl_mlx_cexit_img, \
		mlx_game->sl_mlx_e_img_size, mlx_game->sl_mlx_e_img_size);
}

/**
 * Handles keyboard input events for the game.
 * Moves the player character based on the key pressed.
 * @param keydata - Structure containing key event data.
 * @param param - Pointer to the game structure.
 */
void	ft_hook(mlx_key_data_t keydata, void *param)
{
	mlx_image_t		*player;
	t_sl_mlx_game	*mlx_game;
	t_sl_game		*game;

	game = (t_sl_game *)param;
	mlx_game = game->sl_mlx_game;
	player = mlx_game->sl_mlx_player_img;
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_ESCAPE)
		sl_clean_exit(game, "");
	if (keydata.action == MLX_RELEASE && keydata.key == \
		game->sl_key_right && sl_mlx_move(game, player->instances, 0, 1))
		player->instances[0].x += mlx_game->sl_mlx_w_img_size;
	if (keydata.action == MLX_RELEASE && keydata.key == \
		game->sl_key_left && sl_mlx_move(game, player->instances, 0, -1))
		player->instances[0].x -= mlx_game->sl_mlx_w_img_size;
	if (keydata.action == MLX_RELEASE && keydata.key == \
		game->sl_key_up && sl_mlx_move(game, player->instances, -1, 0))
		player->instances[0].y -= mlx_game->sl_mlx_w_img_size;
	if (keydata.action == MLX_RELEASE && keydata.key == \
		game->sl_key_down && sl_mlx_move(game, player->instances, 1, 0))
		player->instances[0].y += mlx_game->sl_mlx_w_img_size;
	if (game->sl_game_ended == 1)
		sl_clean_exit(game, "");
	return ;
}

/**
 * Starts the game loop by setting up MLX, loading and resizing images,
 * and placing them on the window. Registers the keyboard input hook.
 * @param game - Pointer to the t_sl_game structure.
 * @return EXIT_SUCCESS on successful initialization and game start.
 */
int32_t	sl_mlx_start_game(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	sl_check_game_size(game);
	sl_create_handle(game);
	sl_mlx_load_images(game);
	sl_resize_images(game);
	sl_put_image_background(game);
	sl_put_images_walls(game);
	sl_put_images_closed_exit(game);
	sl_put_image_player(game);
	sl_load_images_colls(game);
	sl_put_images_colls(game);
	mlx_key_hook(mlx_game->sl_mlx_handle, &ft_hook, game);
	mlx_loop(mlx_game->sl_mlx_handle);
	return (EXIT_SUCCESS);
}
