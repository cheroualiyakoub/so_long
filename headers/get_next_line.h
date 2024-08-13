/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:26:18 by ycheroua          #+#    #+#             */
/*   Updated: 2024/05/06 01:23:58 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1084
# endif
///
# include <stdlib.h>
# include <unistd.h>
///

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
}	t_list_gnl;

int			len_to_newline(t_list_gnl *list);
int			new_line_found(t_list_gnl *list);
t_list_gnl	*ft_lst_get_last(t_list_gnl *list);
void		append_buf_list(t_list_gnl **list, char *buf);
void		add_line_to_list(t_list_gnl **list, int fd);
void		list_to_str(t_list_gnl *list, char *str);
char		*finel_line(t_list_gnl *list);
void		free_list(t_list_gnl **list, t_list_gnl *new_node);
void		cleane_list(t_list_gnl **list);
char		*get_next_line(int fd);

#endif