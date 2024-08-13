/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_check_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:25:04 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:49:20 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Checks each character in the map to ensure it is a valid character.
 * If an invalid character is found, the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_check_map_chars(t_sl_game *game)
{
	t_list	*map;
	char	*ligne;
	int		i;

	map = game->sl_map;
	while (map)
	{
		i = -1;
		ligne = map->content;
		while (ligne[++i])
			if (!sl_is_valid_char(game, ligne[i]))
				sl_clean_exit(game, game->sl_messages->sl_err_invalid_char);
		map = map->next;
	}
}

/**
 * Checks if the map is rectangular and meets 
 * 		the minimum size requirements.
 * If the map is not rectangular or too small, 
 * 		the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_check_map_rectangular(t_sl_game *game)
{
	t_list	*map;
	int		line_counts;
	size_t	count_lengh;

	map = game->sl_map;
	line_counts = ft_lstsize(map);
	if (line_counts < 3)
		sl_clean_exit(game, game->sl_messages->sl_err_map_rectangular);
	count_lengh = ft_strlen(map->content);
	if (count_lengh < 3)
		sl_clean_exit(game, game->sl_messages->sl_err_map_rectangular);
	if (count_lengh * line_counts < 15)
		sl_clean_exit(game, game->sl_messages->sl_err_map_to_small);
	map = map->next;
	while (map)
	{
		if (ft_strlen(map->content) != count_lengh)
			sl_clean_exit(game, game->sl_messages->sl_err_map_rectangular);
		map = map->next;
	}
	game->sl_map_linges = line_counts;
	game->sl_map_lengh = count_lengh;
}

/**
 * Checks the map to ensure there is exactly one player character.
 * If there is not exactly one player, the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_check_player(t_sl_game *game)
{
	t_list	*map;
	int		count_p;
	int		i;
	char	*ligne;

	map = game->sl_map;
	count_p = 0;
	while (map)
	{
		i = -1;
		ligne = map->content;
		while (ligne[++i])
			if (ligne[i] == game->sl_player_char)
				count_p++;
		map = map->next;
	}
	if (count_p != 1)
		sl_clean_exit(game, game->sl_messages->sl_err_map_player);
}

/**
 * Checks the map to ensure there is exactly one exit character.
 * If there is not exactly one exit, the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_map_check_exit(t_sl_game *game)
{
	t_list	*map;
	int		count_e;
	int		i;
	char	*ligne;

	map = game->sl_map;
	count_e = 0;
	while (map)
	{
		i = -1;
		ligne = map->content;
		while (ligne[++i])
			if (ligne[i] == game->sl_exit_char)
				count_e++;
		map = map->next;
	}
	if (count_e != 1)
		sl_clean_exit(game, game->sl_messages->sl_err_map_exit);
}

/**
 * Checks if the map is properly surrounded by walls.
 * If the map is not surrounded by walls, the game exits with an error message.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_map_chek_walls(t_sl_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < game->sl_map_lengh)
	{
		if (game->sl_map_array[i][j] != game->sl_walls_char || \
			game->sl_map_array[game->sl_map_linges - 1][j] \
				!= game->sl_walls_char)
			sl_clean_exit(game, game->sl_messages->sl_err_map_walls);
	}
	i = -1;
	j = 0;
	while (++i < game->sl_map_linges)
	{
		if (game->sl_map_array[i][j] != game->sl_walls_char || \
			game->sl_map_array[i][game->sl_map_lengh - 1] \
				!= game->sl_walls_char)
			sl_clean_exit(game, game->sl_messages->sl_err_map_walls);
	}
}
