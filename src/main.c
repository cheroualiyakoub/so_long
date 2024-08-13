/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:49:00 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 17:02:29 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Main function for the game. It parses command-line arguments, initializes
 * the game, sets up the map, starts the graphical interface, and cleans up
 * resources after the game ends. It also provides informative error messages
 * if any issues occur during initialization or memory allocation.
 * 
 * @param argc - Number of command-line arguments.
 * @param argv - Array of command-line argument strings.
 * @return int - Exit status.
 */
int	main(int argc, char **argv)
{
	t_sl_game	*game;

	if (argc != 2)
		return (write(1, "Error\nProgram has to take one argument.\n", 40));
	game = malloc(sizeof(t_sl_game));
	if (!game)
	{
		write(1, "Error\n Error while Allocating memory for game\n", 34);
		return (1);
	}
	game->sl_map_path = argv[1];
	sl_init_config(game);
	sl_set_map_to_game(game);
	sl_init_mlx_game(game);
	sl_mlx_start_game(game);
	sl_clean(game);
	return (0);
}
