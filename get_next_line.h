/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisaacs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:19:07 by iisaacs           #+#    #+#             */
/*   Updated: 2019/07/03 10:55:18 by iisaacs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <stdio.h>
#include <unistd.h>
//#include "libft.h"
#include "libft/includes/libft.h"
#define BUFF_SIZE 100

typedef struct		s_vlst
{
	int				fd;
	char			*content;
	struct s_vlst	*next;
}					t_vlst;

int				get_next_line(const int fd, char **line);

#endif
