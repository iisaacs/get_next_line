/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:19:07 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/01 13:08:39 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#define BUFF_SIZE 50

typedef struct		s_vlst
{
	int				fd;
	char			*content;
	struct s_vlst	*next;
}					t_vlst;

int				get_next_line(const int fd, char **line);

#endif
