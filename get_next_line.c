/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 09:39:27 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/12 12:28:33 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cpy_upd(char **line, char **str)
{
	char	*temp;
	int		len;

	temp = (*str);
	if (ft_strlen(*str) == 0)
		return (NULL);
	if ((*temp) == '\n')
	{
		(*str)++;
		return ("");
	}
	while ((*temp) != '\n' && (*temp) != '\0')
		temp++;
	len = (temp) - (*str);
	if (!(*line = (char *)malloc(len + 1)))
		return (NULL);
	ft_bzero(*line, (len + 1));
	(*line) = ft_strncpy((*line), (*str), len);
	if ((*temp) == '\n')
		(*str)++;
	(*str) += len;
	return ((*line));
}

static char	*read_buff(char *buff, const int fd)
{
	char *temp;
	char *new_str;

	new_str = NULL;
	while (read(fd, buff, BUFF_SIZE))
	{
		temp = new_str;
		new_str = (!new_str) ? ft_strdup((const char*)buff) :
			ft_strjoin(new_str, (const char*)buff);
		free(temp);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	return (new_str);
}

int			get_next_line(const int fd, char **line)
{
	static char *all_files[654321];
	char		buff[BUFF_SIZE + 1];
	static char	*p;

	p = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	if (fd < 0 || !line || BUFF_SIZE < 1 || (read(fd, buff, 0) == -1))
		return (-1);
	if (!all_files[fd])
	{
		all_files[fd] = read_buff(buff, fd);
		p = all_files[fd];
	}
	(*line) = cpy_upd(line, &all_files[fd]);
	if (!(*line))
	{
		free(p);
		return (0);
	}
	return (1);
}
