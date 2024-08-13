/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:28 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/23 17:33:30 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

int	len_to_newline(t_list_gnl *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

int	new_line_found(t_list_gnl *list)
{
	int			i;
	t_list_gnl	*lst_node;

	if (list == NULL)
		return (0);
	i = 0;
	lst_node = ft_lst_get_last(list);
	while (lst_node->content[i] && i < BUFFER_SIZE)
	{
		if (lst_node->content[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

t_list_gnl	*ft_lst_get_last(t_list_gnl *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	append_buf_list(t_list_gnl **list, char *buf)
{
	t_list_gnl	*new_node;
	t_list_gnl	*last_node;

	last_node = ft_lst_get_last(*list);
	new_node = malloc(sizeof(t_list_gnl));
	if (new_node == NULL)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	list_to_str(t_list_gnl *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}
