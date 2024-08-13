/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 02:25:02 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/22 17:52:24 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Writes an error message to stdout, 
 * 		cleans up resources, and exits the program.
 * @param game - Pointer to the t_sl_game structure.
 * @param msg - Error message to be displayed before exiting.
 */
void	sl_clean_exit(t_sl_game *game, char *msg)
{
	write(1, msg, ft_strlen(msg));
	if (ft_strlen(msg) != 0)
		write(1, "\n", 1);
	sl_clean(game);
	exit(1);
}

/**
 * Frees the memory allocated for the messages structure.
 * @param messages - Pointer to the 
 * 		t_sl_messages structure to be freed.
 */
void	sl_free_messages(t_sl_messages *messages)
{
	if (messages)
	{
		if (messages->sl_err_path)
			free(messages->sl_err_path);
		free(messages);
	}
}

/**
 * Frees the memory allocated 
 * 		for the map arrays and sets pointers to NULL.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_free_array_map(t_sl_game *game)
{
	int	i;

	i = -1;
	if (game->sl_map_array)
	{
		while (++i < game->sl_map_linges)
		{
			if (game->sl_map_array[i])
				free(game->sl_map_array[i]);
		}
		free(game->sl_map_array);
		game->sl_map_array = NULL;
	}
	i = -1;
	if (game->sl_map_temp)
	{
		while (++i < game->sl_map_linges)
		{
			if (game->sl_map_temp[i])
				free(game->sl_map_temp[i]);
		}
		free(game->sl_map_temp);
		game->sl_map_temp = NULL;
	}
}

/**
 * Frees the linked list representing the map and its content.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_free_map_list(t_sl_game *game)
{
	t_list	*current;
	t_list	*next;

	current = game->sl_map;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	game->sl_map = NULL;
}

/**
 * Cleans up all resources associated with the game.
 * Frees memory for messages, map list, map arrays, and MLX resources.
 * @param game - Pointer to the t_sl_game structure.
 */
void	sl_clean(t_sl_game *game)
{
	if (game)
	{
		sl_free_messages(game->sl_messages);
		sl_free_map_list(game);
		sl_free_array_map(game);
		sl_clean_mlx(game->sl_mlx_game);
		free(game);
	}
}
