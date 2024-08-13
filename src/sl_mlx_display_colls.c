/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mlx_display_colls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:53:15 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/28 16:55:12 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

/**
 * Returns the last element in a linked list of t_sl_mlx_coll_imgs.
 * @param list - Pointer to the first element of the list.
 * @return Pointer to the last element of the list, or NULL if the list is empty.
 */
t_sl_mlx_coll_imgs	*sl_lstlast(t_sl_mlx_coll_imgs *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/**
 * Adds a new element to the end of a linked list of t_sl_mlx_coll_imgs.
 * @param lst - Pointer to the pointer of the first element of the list.
 * @param new - Pointer to the new element to add.
 */
void	sl_lstadd_back(t_sl_mlx_coll_imgs **lst, t_sl_mlx_coll_imgs *new)
{
	t_sl_mlx_coll_imgs	*last;

	if (lst)
	{
		if (*lst)
		{
			last = sl_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/**
 * Loads collectible images into a linked list based on the map array.
 * @param game - Pointer to the t_sl_game structure containing game data.
 * @param mlx_coll_list - Pointer to the pointer 
 * 		of the first element of the collectible images list.
 * @param mlx_coll_img - Pointer to the current collectible image element.
 * @param i - Initial index for the loop.
 */
void	sl_loop_load_coll(t_sl_game *game, t_sl_mlx_coll_imgs **mlx_coll_list,
			t_sl_mlx_coll_imgs *mlx_coll_img, int i)
{
	int	j;

	while (++i < game->sl_map_linges)
	{
		j = -1;
		while (++j < game->sl_map_lengh)
		{
			if (game->sl_map_array[i][j] == game->sl_collectible_char)
			{
				mlx_coll_img = malloc(sizeof(t_sl_mlx_coll_imgs));
				if (!mlx_coll_img)
					sl_clean_exit(game, game->sl_messages->sl_err_malloc);
				mlx_coll_img->sl_mlx_coll_img = sl_mlx_load_png(game, \
						game->sl_mlx_game->sl_mlx_c_img_path);
				if (!mlx_coll_img->sl_mlx_coll_img)
					sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
				mlx_coll_img->x = i;
				mlx_coll_img->y = j;
				mlx_coll_img->next = NULL;
				sl_lstadd_back(mlx_coll_list, mlx_coll_img);
			}
		}
	}
}

/**
 * Initializes and loads collectible images into the game's mlx structure.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_load_images_colls(t_sl_game *game)
{
	t_sl_mlx_game		*mlx_game;
	t_sl_mlx_coll_imgs	**mlx_coll_list;
	t_sl_mlx_coll_imgs	*mlx_coll_img;

	mlx_game = game->sl_mlx_game;
	mlx_coll_list = malloc(sizeof(t_sl_mlx_coll_imgs *));
	if (!mlx_coll_list)
		sl_clean_exit(game, game->sl_messages->sl_err_malloc);
	*mlx_coll_list = NULL;
	mlx_game->sl_colls_imgs = mlx_coll_list;
	mlx_coll_img = NULL;
	sl_loop_load_coll(game, mlx_coll_list, mlx_coll_img, -1);
}

/**
 * Places collectible images 
 * 		onto the game window at their respective positions.
 * @param game - Pointer to the t_sl_game structure containing game data.
 */
void	sl_put_images_colls(t_sl_game *game)
{
	t_sl_mlx_game		*mlx_game;
	t_sl_mlx_coll_imgs	**mlx_coll_list;
	t_sl_mlx_coll_imgs	*mlx_coll_img;

	mlx_game = game->sl_mlx_game;
	mlx_coll_list = mlx_game->sl_colls_imgs;
	mlx_coll_img = *mlx_coll_list;
	while (mlx_coll_img)
	{
		sl_mlx_resize_image(game, mlx_coll_img->sl_mlx_coll_img, \
			mlx_game->sl_mlx_c_img_size, \
			mlx_game->sl_mlx_c_img_size);
		if (mlx_image_to_window(mlx_game->sl_mlx_handle,
				mlx_coll_img->sl_mlx_coll_img,
				mlx_game->sl_mlx_w_img_size * mlx_coll_img->y,
				mlx_game->sl_mlx_w_img_size * mlx_coll_img->x) == -1)
			sl_clean_exit(game, (char *)mlx_strerror(mlx_errno));
		mlx_coll_img = mlx_coll_img->next;
	}
	mlx_coll_img = *mlx_coll_list;
}
