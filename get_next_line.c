/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 08:53:32 by iisaacs           #+#    #+#             */
/*   Updated: 2019/06/25 17:16:32 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./iisaacs/libft.h"
#define BUFF_SIZE 30

typedef struct		s_vlst
{
	int				fd;
	char			*content;
	struct s_vlst	*next;
}					t_vlst;


void	print_values(t_vlst *old_node)
{
	int		i = 0;

	t_vlst *node;

	node = old_node;
	while (node != NULL)
	{
		printf("At: %d\n", i);
		printf("Fd: %d\n", node->fd);
		printf("Content: %s**", node->content);
		node = node->next;
		i++;
	}
}

/*
 ** Create and add new node at beginning of list
 ** with fd and content.
 */
static t_vlst	*vlstnew(t_vlst **head, int fd, char *content)
{
	t_vlst *new_node;
	
	if (!head)
	{
		*head = (t_vlst*)malloc(sizeof(t_vlst));
		(*head)->fd = fd;
		(*head)->content = content;
		(*head)->next = NULL;
	}
	else
	{
		new_node = (t_vlst*)malloc(sizeof(t_vlst));
		new_node->fd = fd;
		new_node->content = content;
		new_node->next = (*head);
		(*head) = new_node;
	}
	return ((*head));
}

/*
 ** Check if fd is in list (reverenced by head)
 */ 
static	int	is_fd_lst(int fd, t_vlst *head)
{
	t_vlst *current;

	current = head;
	while (current != NULL)
	{
		printf("fd and node's fd: %d, %d\n", fd, current->fd);
		if (fd == current->fd)
			return (1);
		current = current->next;
	}
	return (0);
}

static char	*ret_line(char **data)
{
	int		i;
	char	*line;
	char	*ret_data;
	int		len;

	i = 0;
	if (!(*data))
		return (NULL);
	ret_data = (*data);
	while (ret_data[i] != '\n' && ret_data[i])
		i++;
	if (ret_data[i] == '\n' || ret_data[i] == '\0')
		i++;
	line = ft_strsub((const char*)(*data), 0, i - 1);
	(*data) = &ret_data[i];
	return (line);
}

/*  so far..
 ** if fd is in list...
 **	else, read from fd to buff. Then copy and join buff to new_str
 **    then create node with content and fd.
 */

void/*int*/		get_next_line(const int fd, char **line)
{
	char			*buff[BUFF_SIZE];
	char			*new_str;
	char			*temp;
	int				ret;
	static t_vlst	*head;

	ft_bzero(buff, BUFF_SIZE);
	new_str = NULL;
	if (is_fd_lst(fd, head))
	{
		;
	}
	else
	{
		while ((ret = read(fd, buff, BUFF_SIZE)))
		{
			if (!new_str)
			{
				temp = ft_strjoin("", (const char*)buff);
				new_str = temp;
			}
			else
			{
				temp = ft_strjoin(new_str, (const char*)buff);
				new_str = temp;
				ft_bzero(buff, BUFF_SIZE);
			}
		}
		head = vlstnew(&head, 0, new_str);
	}
}

int			main()
{
	char *str = "sup\nmy nigga\nshut up";
	char *line;

	line = ret_line(&str);
	printf("line: **%s**\n", line);
	printf("str: %s\n\n", str);

	line = ret_line(&str);
	printf("line: **%s**\n", line);
	printf("str: %s\n\n", str);

	line = ret_line(&str);
	printf("line: **%s**\n", line);
	printf("str: %s\n\n", str);
}
