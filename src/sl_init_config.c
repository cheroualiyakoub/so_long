/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_init_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 02:28:39 by ycheroua          #+#    #+#             */
/*   Updated: 2024/08/13 17:21:06 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Initializes secondary error and informational messages for the game.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_init_messages_2(t_sl_game *game)
{
	t_sl_messages	*sl_messages;

	sl_messages = game->sl_messages;
	sl_messages->sl_err_map_walls = "\
		Error\nMap should be surrounded by walls '1'.";
	game->sl_messages->sl_err_invalid_char = \
		"Error\nMap countains invalid characters.";
	game->sl_messages->sl_err_map_rich_collectible = \
		"Error\nOne or more collectibles can not be riched.";
	game->sl_messages->sl_err_map_rich_exit = \
		"Error\nPlayer can't rich the exit.";
	game->sl_messages->sl_movement_prompt = "Current number of movements = ";
	sl_messages->sl_movement_prompt = "Current number of movements = ";
	sl_messages->sl_mlx_resize_img = \
		"Error\nAccured while resizing an image.";
	sl_messages->sl_mlx_err_size_monitor = \
		"Error\nMap size is too big for this monitor.";
	sl_messages->sl_err_png_path = "Error\nPNG file data wrong!";
}

/**
 * Initializes primary error and informational messages for the game.
 * Allocates memory for the messages structure and sets default messages.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_init_messages(t_sl_game *game)
{
	t_sl_messages	*sl_messages;

	game->sl_messages = malloc(sizeof(t_sl_messages));
	sl_messages = game->sl_messages;
	if (!(game->sl_messages))
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	game->sl_messages->sl_err_extension = \
		"Error\nMap file extention is wrong (It should be .ber).";
	sl_messages->sl_err_path = ft_strjoin("Error\nA \
		problem occurred while opnening a file: ", game->sl_map_path);
	if (!(game->sl_messages->sl_err_path))
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	game->sl_messages->sl_err_malloc = \
		"Error\nError while trying to access the storage.";
	sl_messages->sl_err_map_player = "Error\nMap should contain one Player.";
	game->sl_messages->sl_err_map_exit = "Error\nMap should contain one Exit.";
	game->sl_messages->sl_err_map_count_collectible = \
		"Error\nMap should contain at least one collectible.";
	game->sl_messages->sl_err_map_rectangular = "Map should be rectangular.";
	sl_messages->sl_err_map_to_small = \
		"Error\nMap too small to contain all components.";
	sl_init_messages_2(game);
}

/**
 * Initializes the game configuration with default values.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_init_config(t_sl_game *game)
{
	sl_init_messages(game);
	game->sl_map_path_extension = ".ber";
	game->sl_player_char = 'P';
	game->sl_exit_char = 'E';
	game->sl_collectible_char = 'C';
	game->sl_walls_char = '1';
	game->sl_empty_char = '0';
	game->sl_eated_coll = 0;
	game->sl_riched_exit = 0;
	game->sl_game_ended = 0;
	game->sl_map_max_size_width = 2520;
	game->sl_map_max_size_height = 1280;
	game->sl_count_movements = 0;
	game->sl_mlx_game = NULL;
	game->sl_map = NULL;
	game->sl_map_array = NULL;
	game->sl_map_temp = NULL;
	game->sl_key_up = 87;
	game->sl_key_down = 83;
	game->sl_key_right = 68;
	game->sl_key_left = 65;
}

/**
 * Initializes the MiniLibX game 
 * 		instance with default values and settings.
 * Allocates memory for the t_sl_mlx_game 
 * 		structure and sets image paths and sizes.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_init_mlx_game(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = malloc(sizeof(t_sl_mlx_game));
	if (!mlx_game)
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	mlx_game->mlx_game_name = "So long";
	mlx_game->sl_mlx_w_img_path = "./textures/brick1.png";
	mlx_game->sl_mlx_p_img_path = "./textures/naruto.png";
	mlx_game->sl_mlx_c_img_path = "./textures/ramen.png";
	mlx_game->sl_mlx_b_img_path = "./textures/background.png";
	mlx_game->sl_mlx_ce_img_path = "./textures/closed_door.png";
	mlx_game->sl_mlx_oe_img_path = "./textures/open_door.png";
	mlx_game->sl_mlx_p_img_size = 40;
	mlx_game->sl_mlx_c_img_size = 30;
	mlx_game->sl_mlx_w_img_size = 40;
	mlx_game->sl_mlx_e_img_size = 40;
	mlx_game->sl_mlx_window_width = \
		game->sl_map_lengh * mlx_game->sl_mlx_w_img_size;
	mlx_game->sl_mlx_window_height = \
		game->sl_map_linges * mlx_game->sl_mlx_w_img_size;
	mlx_game->sl_mlx_b_img_size_x = mlx_game->sl_mlx_window_width;
	mlx_game->sl_mlx_b_img_size_y = mlx_game->sl_mlx_window_height;
	game->sl_mlx_game = mlx_game;
	game->sl_mlx_game->sl_colls_imgs = NULL;
	game->sl_mlx_game->sl_mlx_handle = NULL;
}
