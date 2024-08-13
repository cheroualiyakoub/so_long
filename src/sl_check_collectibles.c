/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_check_collectibles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:16:48 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:45:33 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Allocates memory for a temporary 
 * 		map and copies the content from the original map array.
 * This temporary map is used for further processing like pathfinding.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_set_temp_map(t_sl_game *game)
{
	int	i;
	int	j;

	game->sl_map_temp = malloc(game->sl_map_linges * sizeof(char *));
	if (!(game->sl_map_temp))
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	i = -1;
	while (++i < game->sl_map_linges)
	{
		j = -1;
		game->sl_map_temp[i] = malloc(game->sl_map_lengh * sizeof(char));
		if (!(game->sl_map_temp[i]))
			sl_clean_exit(game, game->sl_messages->sl_err_malloc);
		while (++j < game->sl_map_lengh)
		{
			game->sl_map_temp[i][j] = game->sl_map_array[i][j];
		}
	}
}

/**
 * Sets the start positions of the player and the exit on the map.
 * These positions are used to track 
 * 		the player's movements and check game conditions.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_set_start_positions(t_sl_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->sl_map_linges)
	{
		j = -1;
		while (++j < game->sl_map_lengh)
		{
			if (game->sl_map_temp[i][j] == game->sl_player_char)
			{
				game->sl_start_positon_x = i;
				game->sl_start_positon_y = j;
			}
			if (game->sl_map_temp[i][j] == game->sl_exit_char)
			{
				game->sl_exit_positon_x = i;
				game->sl_exit_positon_y = j;
			}
		}
	}
}

/**
 * Counts the number of collectibles on the map.
 * If there are no collectibles, the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_map_count_collectible(t_sl_game *game)
{
	t_list	*map;
	int		i;
	char	*ligne;

	map = game->sl_map;
	game->sl_count_collectible = 0;
	while (map)
	{
		i = -1;
		ligne = map->content;
		while (ligne[++i])
			if (ligne[i] == game->sl_collectible_char)
				game->sl_count_collectible++;
		map = map->next;
	}
	if (game->sl_count_collectible == 0)
		sl_clean_exit(game, game->sl_messages->sl_err_map_count_collectible);
}

/**
 * Checks if all collectibles can be reached 
 * 		and if the exit can be reached by the player.
 * If not, the game exits with an appropriate error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_rich_coll_exit(t_sl_game *game)
{
	game->sl_count_coll_temp = game->sl_count_collectible;
	sl_flood_fill(game,
		game->sl_start_positon_y,
		game->sl_start_positon_y);
	if (game->sl_count_coll_temp != 0)
		sl_clean_exit(game, game->sl_messages->sl_err_map_rich_collectible);
	if (game->sl_riched_exit == 0)
		sl_clean_exit(game, game->sl_messages->sl_err_map_rich_exit);
}
