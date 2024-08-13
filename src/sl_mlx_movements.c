/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:49:24 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 17:00:41 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Checks if the player can move to the specified position.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param x - The x-coordinate of the position to check.
 * @param y - The y-coordinate of the position to check.
 * @return 1 if the player can move to the position, 0 otherwise.
 */
int	sl_mlx_can_move(t_sl_game *game, int x, int y)
{
	char	**sl_array;

	sl_array = game->sl_map_array;
	if (sl_array[x][y] != game->sl_walls_char)
		return (1);
	return (0);
}

/**
 * Removes the closed exit image from 
 * 		the game window and adds the open exit image.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_mlx_last_coll(t_sl_game *game)
{
	t_sl_mlx_game	*mlx_game;

	mlx_game = game->sl_mlx_game;
	mlx_delete_image(mlx_game->sl_mlx_handle, mlx_game->sl_mlx_cexit_img);
	mlx_game->sl_mlx_cexit_img = NULL;
	sl_put_images_open_exit(game);
}

/**
 * Handles the player's movement to a position containing a collectible.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param x - The x-coordinate of the position containing the collectible.
 * @param y - The y-coordinate of the position containing the collectible.
 */
void	sl_mlx_is_move_to_coll(t_sl_game *game, uint32_t x, uint32_t y)
{
	t_sl_mlx_game		*mlx_game;
	t_sl_mlx_coll_imgs	*mlx_coll_img;

	if (game->sl_map_array[x][y] == game->sl_collectible_char)
	{
		mlx_game = game->sl_mlx_game;
		mlx_coll_img = *(mlx_game->sl_colls_imgs);
		while (mlx_coll_img)
		{
			if (mlx_coll_img->x == x && mlx_coll_img->y == y)
			{
				mlx_delete_image(mlx_game->sl_mlx_handle,
					mlx_coll_img->sl_mlx_coll_img);
				mlx_coll_img->sl_mlx_coll_img = NULL;
				game->sl_eated_coll += 1;
				game->sl_map_array[x][y] = game->sl_empty_char;
				break ;
			}
			mlx_coll_img = mlx_coll_img->next;
		}
		if (game->sl_count_collectible == game->sl_eated_coll)
			sl_mlx_last_coll(game);
	}
	return ;
}

/**
 * Handles the player's movement to the exit position.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param x - The x-coordinate of the position containing the exit.
 * @param y - The y-coordinate of the position containing the exit.
 */
void	sl_mlx_is_move_to_exit(t_sl_game *game, int x, int y)
{
	if (game->sl_map_array[x][y] == game->sl_exit_char && \
			game->sl_count_collectible == game->sl_eated_coll)
		game->sl_game_ended = 1;
}

/**
 * Moves the player in the game world based on the specified movement parameters.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param instances - Pointer to the instance structure representing the player.
 * @param move_x - The amount to move in the x-direction.
 * @param move_y - The amount to move in the y-direction.
 * @return 1 if the player can move to the specified position, 0 otherwise.
 */
int	sl_mlx_move(t_sl_game *game,
		mlx_instance_t *instances, int move_x, int move_y)
{
	char	**sl_array;
	int		x;
	int		y;

	sl_array = game->sl_map_array;
	x = (instances->y / game->sl_mlx_game->sl_mlx_w_img_size) + move_x;
	y = (instances->x / game->sl_mlx_game->sl_mlx_w_img_size) + move_y;
	if (sl_mlx_can_move(game, x, y))
	{
		game->sl_count_movements++;
		write(1, game->sl_messages->sl_movement_prompt,
			ft_strlen(game->sl_messages->sl_movement_prompt));
		ft_putnbr_fd(game->sl_count_movements, 1);
		write(1, "\n", 1);
		sl_mlx_is_move_to_coll(game, (uint32_t) x, (uint32_t)y);
		sl_mlx_is_move_to_exit(game, x, y);
		return (1);
	}
	return (0);
}
