/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:03:57 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:34:43 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Checks if the map path is valid and accessible.
 * Ensures the file extension 
 * 		is correct and the file can be opened.
 * @param game - Pointer to the t_sl_game structure.
 * @return File descriptor if successful, exits on failure.
 */
int	sl_check_map_path(t_sl_game *game)
{
	int	fd;
	int	index_extentions;

	if (game->sl_map_path == NULL)
		return (0);
	if (ft_strlen(game->sl_map_path) < ft_strlen(game->sl_map_path_extension))
		sl_clean_exit(game, game->sl_messages->sl_err_extension);
	index_extentions = ft_strlen(game->sl_map_path) - \
		ft_strlen(game->sl_map_path_extension);
	if (ft_strcmp(&game->sl_map_path[index_extentions],
			game->sl_map_path_extension) != 0)
		sl_clean_exit(game, game->sl_messages->sl_err_extension);
	fd = open(game->sl_map_path, O_RDONLY);
	if (fd < 2)
		sl_clean_exit(game, game->sl_messages->sl_err_path);
	return (fd);
}

/**
 * Reads the map from the file and stores it in the game's map list.
 * Each line of the map is added as a node in the linked list.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_read_map(t_sl_game *game)
{
	int		fd;
	int		keep_reading;
	char	*line;
	t_list	*map_line;

	fd = sl_check_map_path(game);
	keep_reading = 1;
	while (keep_reading)
	{
		line = get_next_line(fd);
		if (line && ft_strchr(line, '\n'))
			line[ft_strlen(line) - 1] = '\0';
		if (line == NULL)
		{
			keep_reading = 0;
			break ;
		}
		map_line = ft_lstnew(line);
		if (map_line == NULL)
			sl_clean_exit(game, game->sl_messages->sl_err_malloc);
		ft_lstadd_back(&game->sl_map, map_line);
	}
	close(fd);
}

/**
 * Converts the map linked list into a 2D array for easier processing.
 * Allocates memory for the array and duplicates each line from the list.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_set_array_map(t_sl_game *game)
{
	t_list	*temp_map_node;
	int		i;

	i = 0;
	game->sl_map_array = malloc(sizeof(char *) * ft_lstsize(game->sl_map));
	if (!game->sl_map_array)
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	temp_map_node = game->sl_map;
	while (i < ft_lstsize(game->sl_map))
	{
		game->sl_map_array[i] = ft_strdup(temp_map_node->content);
		if (!game->sl_map_array[i])
			sl_clean_exit(game, game->sl_messages->sl_err_malloc);
		temp_map_node = temp_map_node->next;
		i++;
	}
}

/**
 * Sets up the game map by reading 
 * 		the map file and validating its content.
 * Calls various functions to check 
 * 		the map's structure and initialize game elements.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_set_map_to_game(t_sl_game *game)
{
	sl_read_map(game);
	sl_check_map_chars(game);
	sl_check_map_rectangular(game);
	sl_check_player(game);
	sl_map_check_exit(game);
	sl_map_count_collectible(game);
	sl_set_array_map(game);
	sl_map_chek_walls(game);
	sl_set_temp_map(game);
	sl_set_start_positions(game);
	sl_rich_coll_exit(game);
}
