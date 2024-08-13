/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:00:22 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:42:26 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Cleans up and frees the memory allocated for collectible images.
 * Deletes images using the MLX handle and frees the list nodes.
 * @param mlx_game - Pointer to the t_sl_mlx_game structure.
 */
void	sl_mlx_clean_coll_imgs(t_sl_mlx_game *mlx_game)
{
	t_sl_mlx_coll_imgs	*current;
	t_sl_mlx_coll_imgs	*next;

	if (mlx_game->sl_colls_imgs)
	{
		current = *(mlx_game->sl_colls_imgs);
		while (current != NULL)
		{
			next = current->next;
			if (current->sl_mlx_coll_img)
			{
				mlx_delete_image(mlx_game->sl_mlx_handle,
					current->sl_mlx_coll_img);
				current->sl_mlx_coll_img = NULL;
			}
			free(current->sl_mlx_coll_img);
			free(current);
			current = next;
		}
		free(mlx_game->sl_colls_imgs);
		mlx_game->sl_colls_imgs = NULL;
	}
}

/**
 * Cleans up and frees all MLX-related resources, 
 * 		including images and the MLX handle.
 * Deletes images using the MLX handle
 * 		 and frees the MLX game structure.
 * @param mlx_game - Pointer to the t_sl_mlx_game structure.
 */
void	sl_clean_mlx(t_sl_mlx_game *mlx_game)
{
	if (mlx_game)
	{
		if (mlx_game->sl_mlx_handle)
		{
			sl_mlx_clean_coll_imgs(mlx_game);
			if (mlx_game->sl_mlx_player_img)
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_game->sl_mlx_player_img);
			if (mlx_game->sl_mlx_backgrnd_img)
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_game->sl_mlx_backgrnd_img);
			if (mlx_game->sl_mlx_wall_img)
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_game->sl_mlx_wall_img);
			if (mlx_game->sl_mlx_cexit_img)
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_game->sl_mlx_cexit_img);
			if (mlx_game->sl_mlx_oexit_img)
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_game->sl_mlx_oexit_img);
			mlx_terminate(mlx_game->sl_mlx_handle);
			mlx_game->sl_mlx_handle = NULL;
		}
		free(mlx_game);
	}
}
