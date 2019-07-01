/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 10:12:49 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/01 15:40:43 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*void	print_values(t_vlst *old_node)
{
	int		i = 0;

	t_vlst *node;

	node = old_node;
	while (node != NULL)
	{
		printf("-------------------------\n");
		printf("At: %d\n", i);
		printf("Fd: %d\n", node->fd);
		printf("Content: \n%s**\n", node->content);
		printf("-------------------------");
		node = node->next;
		i++;
	}
}*/

/*
 ** Add node to beginning of list.
 ** if head is NULL, create node with fd and content. And point next to NULL.
 **	if head exist, create node with fd and content. And point next to previous head.
 ** return created node.
 */
static t_vlst	*add_vlst(t_vlst **head, int fd, char *content)
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
 ** Check if fd is in list (reverenced by head), if True point found to node. And return True.
 ** Else return False.
 */
static	int	is_fd_lst(int fd, t_vlst *head, t_vlst **found)
{
	t_vlst *current;

	current = head;
	while (current)
	{
		if (fd == current->fd)
		{
			*found = current;
			return (1);
		}
		current = current->next;
	}
	return (0);
}


static char	*cpy_upd(char **data)
{
	int		i;
	char	*line;
	char	*ret_data;

	i = 0;
	if (!(*data))
		return (NULL);
	ret_data = (*data);
	while (ret_data[i] != '\n' && ret_data[i])
		i++;
	line = ft_strsub((const char*)(*data), 0, i);
	if (ret_data[i] == '\n')
		i++;
	else if (ret_data[i] == '\0')
		return (NULL);
	(*data) = &ret_data[i];
	return (line);
}

/*
 ** if fd does not exist in list, create new node
 ** containing fd and new_str.
 ** Copy from new node's content (char pointer) to '\n', in line.
 */
int		get_next_line(const int fd, char **line)
{
	char			*buff[BUFF_SIZE + 1];
	char			*temp;
	char			*new_str;
	int				ret;
	static	t_vlst	*head;
	t_vlst			*found;

	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd < 0 || line == NULL)
		return (-1);
	if (!is_fd_lst(fd, head, &found))
	{
		while ((ret = read(fd, buff, BUFF_SIZE)))
		{
			if (ret < 0)
				return (-1);
			temp = new_str;
			if (!new_str)
				new_str = ft_strjoin("", (const char*)buff);
			else
				new_str = ft_strjoin(new_str, (const char*)buff);
			free(temp);
			ft_bzero(buff, ret);
		}
		found = add_vlst(&head, fd, new_str);
	}
	if (!((*line) = cpy_upd(&(found->content))))
		return (0);
	return (1);
}

int		main()
{

}
