/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:05:54 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 17:00:25 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Loads a PNG image from the specified path and returns an mlx_image_t pointer.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param sl_img_path - Path to the PNG image file.
 * @return mlx_image_t* - Pointer to the loaded image.
 */
mlx_image_t	*sl_mlx_load_png(t_sl_game *game, char *sl_img_path)
{
	t_sl_mlx_game	*mlx_game;
	mlx_texture_t	*texture;
	mlx_image_t		*sl_mlx_img;

	mlx_game = game->sl_mlx_game;
	texture = mlx_load_png(sl_img_path);
	if (!texture)
		sl_clean_exit(game, game->sl_messages->sl_err_png_path);
	sl_mlx_img = mlx_texture_to_image(mlx_game->sl_mlx_handle, texture);
	mlx_delete_texture(texture);
	texture = NULL;
	if (!sl_mlx_img)
		sl_clean_exit(game, game->sl_messages->sl_err_png_path);
	return (sl_mlx_img);
}

/**
 * Resizes an mlx_image_t to the specified dimensions.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param img - Pointer to the image to resize.
 * @param x - New width of the image.
 * @param y - New height of the image.
 */
void	sl_mlx_resize_image(t_sl_game *game, \
	mlx_image_t *img, uint32_t x, uint32_t y)
{
	if (!mlx_resize_image(img, x, y))
		sl_clean_exit(game, game->sl_messages->sl_mlx_resize_img);
}

/**
 * Checks if the game map size exceeds the maximum size allowed by the window.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_check_game_size(t_sl_game *game)
{
	if (game->sl_map_lengh * (int)(game->sl_mlx_game->sl_mlx_w_img_size) > \
		game->sl_map_max_size_width)
		sl_clean_exit(game, game->sl_messages->sl_mlx_err_size_monitor);
	if (game->sl_map_linges * (int)(game->sl_mlx_game->sl_mlx_w_img_size) > \
		game->sl_map_max_size_height)
		sl_clean_exit(game, game->sl_messages->sl_mlx_err_size_monitor);
}
