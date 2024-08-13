/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_check_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:57:33 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:51:01 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Checks if a character in the map is valid.
 * Valid characters are: exit, empty, walls, player, and collectible.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param c - Character to check.
 * @return 1 if the character is valid, 0 otherwise.
 */
int	sl_is_valid_char(t_sl_game *game, char c)
{
	if (c == game->sl_exit_char || c == game->sl_empty_char || \
		c == game->sl_walls_char || c == game->sl_player_char || \
		c == game->sl_collectible_char)
		return (1);
	return (0);
}

/**
 * Performs a flood fill algorithm to check the connectivity of the map.
 * It ensures all collectibles and the 
 * 		exit are reachable from the player's starting position.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param index_x - Current x index in the map.
 * @param index_y - Current y index in the map.
 */
void	sl_flood_fill(t_sl_game *game, int index_x, int index_y)
{
	if (game->sl_map_temp[index_x][index_y] == game->sl_collectible_char)
		game->sl_count_coll_temp--;
	if (game->sl_map_temp[index_x][index_y] == game->sl_exit_char)
		game->sl_riched_exit = 1;
	game->sl_map_temp[index_x][index_y] = game->sl_walls_char;
	if (game->sl_map_temp[index_x][index_y + 1] != game->sl_walls_char)
		sl_flood_fill(game, index_x, index_y + 1);
	if (game->sl_map_temp[index_x + 1][index_y] != game->sl_walls_char)
		sl_flood_fill(game, index_x + 1, index_y);
	if (game->sl_map_temp[index_x][index_y - 1] != game->sl_walls_char)
		sl_flood_fill(game, index_x, index_y - 1);
	if (game->sl_map_temp[index_x - 1][index_y] != game->sl_walls_char)
		sl_flood_fill(game, index_x - 1, index_y);
}
