/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:08 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/23 17:33:13 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

void	add_line_to_list(t_list_gnl **list, int fd)
{
	char	*buf;
	size_t	char_read;

	while (!new_line_found(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append_buf_list(list, buf);
	}
}

char	*finel_line(t_list_gnl *list)
{
	int		str_len;
	char	*result_line;

	str_len = len_to_newline(list);
	if (NULL == list)
		return (NULL);
	result_line = malloc(sizeof(char) * (str_len + 1));
	if (result_line == NULL)
	{
		free(result_line);
		return (NULL);
	}
	list_to_str(list, result_line);
	return (result_line);
}

void	free_list(t_list_gnl **list, t_list_gnl *new_node)
{
	t_list_gnl	*current;
	t_list_gnl	*next;

	current = *list;
	if (*list == NULL )
		return ;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*list = NULL;
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	if (new_node && new_node->content[0])
		*list = new_node;
	else
	{
		free(new_node->content);
		free(new_node);
	}
}

void	cleane_list(t_list_gnl **list)
{
	t_list_gnl	*last;
	t_list_gnl	*new_node;
	int			i;
	int			len;

	last = ft_lst_get_last(*list);
	i = 0;
	len = 0;
	new_node = malloc(sizeof(t_list_gnl));
	if (list == NULL || new_node == NULL || !last)
		return ;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	while (last->content[len])
		len++;
	new_node->content = malloc(sizeof(char) * (len - i) + 1);
	len = 0;
	if (new_node->content == NULL)
		return ;
	while (last->content[i])
		new_node->content[len++] = last->content[i++];
	new_node->content[len] = '\0';
	free_list(list, new_node);
}

char	*get_next_line(int fd)
{
	static t_list_gnl	*list = NULL;
	char				*result_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &result_line, 0) < 0)
	{
		free_list(&list, NULL);
		return (0);
	}
	add_line_to_list(&list, fd);
	if (list == NULL)
		return (NULL);
	result_line = finel_line(list);
	if (result_line == NULL)
		return (NULL);
	cleane_list(&list);
	if (result_line[0] == '\0')
	{
		free_list(&list, NULL);
		return (NULL);
	}
	return (result_line);
}
