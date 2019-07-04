/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:57:49 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/04 13:00:09 by iisaacs          ###   ########.fr       */
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
		printf("\n-------------------------\n");
		printf("At: %d\n", i);
		printf("Fd: %d\n", node->fd);
		printf("Content: \n%s**\n", node->content);
		printf("-------------------------\n");
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

/* 
 ** Returns the copied string (from pointer to '\n')
 ** And update pointer to after the newline.
 */
 static int	cpy_upd(char **data, char **line)
{
	char	*str;
	int		len;

	str = (*data);
	if ((*str) == '\n')
	{
		str++;
		(*data) = str;
		(*line) = NULL;
		return (1);
	}
	while (*str != '\n' && (*str)) // increment pointer to '\n'
		str++;
	len = str - (*data);  // get number of characters from pointer to '\n'
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

	new_str = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd < 0 || !line)
		return (-1);
	if (!is_fd_lst(fd, head, &found))
	{
		while ((ret = read(fd, buff, BUFF_SIZE)))
		{
			if (ret < 0)
				return (-1);
			temp = new_str;
			if (!new_str)
				new_str = ft_strdup((const char*)buff);
			else
				new_str = ft_strjoin(new_str, (const char*)buff);
			free(temp);
			ft_bzero(buff, ret);
		}
		found = add_vlst(&head, fd, new_str);
	}
	if (!(cpy_upd(&(found->content), line)))
		return (0);
	return (1);
}

int		main()
{
	char *line;
	
	char *str = "hello\nmy\nslim\n";
	t_vlst *node;
	node = (t_vlst*)malloc(sizeof(t_vlst));
	node->content = str;
	node->next = NULL;
	node->fd = 0;

	while(cpy_upd(&(node->content), &line))
		printf("line: %s\n", line);

}
