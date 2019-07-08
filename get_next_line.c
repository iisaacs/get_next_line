/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:57:49 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/08 13:21:36 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**Function to add node to beginning of list.
**If the head does not exist. Create new_node.
**And initialize its member with fd and content.
**Set the next to NULL.
**If head points to node. Create new node.
**Initialize members with fd and content.
**And set next to previous head. New node is now the head.
**Return head of list.
*/

static t_vlst	*add_vlst(t_vlst **head, int fd, char *content)
{
	t_vlst *new_node;

	if (!head)
	{
		*head = (t_vlst*)malloc(sizeof(t_vlst));
		(*head)->fd = fd;
		(*head)->start = content;
		(*head)->content = content;
		(*head)->next = NULL;
	}
	else
	{
		new_node = (t_vlst*)malloc(sizeof(t_vlst));
		new_node->fd = fd;
		new_node->start = content;
		new_node->content = content;
		new_node->next = (*head);
		(*head) = new_node;
	}
	return ((*head));
}

/*
** Check if fd is in list.
** if it is, initialize 'found' to desired node.
** return TRUE.
** Otherwise return FALSE.
*/

static int		is_fd_lst(int fd, t_vlst *head, t_vlst **found)
{
	t_vlst *current;

	current = head;
	while (current)
	{
		if (fd == current->fd)
		{
			(*found) = current;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/*
**Function to copy line from string (*data).
**And to update the string pointer to after
**the '\n' character.
**If line at end of function contains nothing return 0;
**Else return 1
*/

static int		cpy_upd(char **data, char **line)
{
	char	*str;
	int		len;

	str = (*data);
	if ((*str) == '\n')
	{
		(*data) = ++str;
		(*line) = "";
		return (1);
	}
	while (*str != '\n' && (*str))
		str++;
	len = str - (*data);
	if (!((*line) = (char *)malloc(sizeof(char) * (len + 1))))
		line = NULL;
	ft_bzero((*line), (size_t)(len + 1));
	(*line) = ft_strncpy((*line), (*data), len);
	if (ft_strlen((*line)) == 0)
		return (0);
	if ((*str) == '\n')
		str++;
	(*data) = str;
	return (1);
}

static char		*read_buff(int fd, char *buff, char *new_str, int *ret)
{
	char	*temp;

	temp = NULL;
	new_str = NULL;
	while ((*ret = read(fd, buff, BUFF_SIZE)))
	{
		if (*ret < 0)
			return (NULL);
		temp = new_str;
		new_str = (!new_str) ? ft_strdup((const char*)buff) :
			ft_strjoin(new_str, (const char*)buff);
		free(temp);
		ft_bzero(buff, *ret);
	}
	return (new_str);
}

int				get_next_line(const int fd, char **line)
{
	char			*buff[BUFF_SIZE + 1];
	char			*new_str;
	static	t_vlst	*head;
	t_vlst			*found;
	int				ret;

	new_str = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!is_fd_lst(fd, head, &found))
	{
		new_str = read_buff(fd, (char *)buff, new_str, &ret);
		if (ret < 0)
			return (-1);
		if (!new_str)
			return (0);
		found = add_vlst(&head, fd, new_str);
	}
	if (!(cpy_upd(&(found->content), line)))
	{
		free(found->start);
		return (0);
	}
	return (1);
}
